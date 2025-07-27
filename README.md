PinAffinity - A simple CPU affinity setter for virtual pin cabs

This is a very simple CPU affinity tool for Windows, designed
specifically for virtual pin cab PCs.  The goal is to provide a the
basic CPU affinity controls most useful on a pin cab, with minimal
user effort for configuration.  

CPU affinity is one of the more useful tools on Windows for improving
video game performance (and virtual pinball is fundamentally a video
game), but it's probably also one of the lesser used tools because
it's not all that accessible in the standard Windows tool set.

The way to use CPU affinity to improve gaming performance is to
partition the CPU cores into groups assigned to "gaming" and
"everything else".  This gives the game software almost exclusive use
of one or more designated cores.

The reason this helps is that it can reduce latency in scheduling game
threads.  The tricky thing to understand here is that we're not
talking about CPU cycles or how high the "% CPU" meter is reading for
a given core.  What we're concerned with here is *scheduling latency*.
That's the amount of time it takes for Windows to get around to
resuming a suspended thread when that thread is ready to run again.
For general software, that latency figure isn't very important,
because what most software cares about is overall throughput - how
many CPU cycles the program is getting, averaged over the long haul.
But that long-term averaging doesn't work well for video games.  For
video games, it's very important to do each individual video update
and physics model update at exactly the right moment, so that the
video animation is smooth and matches up with real time.  That's why
latency is so important for video games.  When a video game thread is
ready to run, it's critical that Windows runs it *right away*.

How does core affinity help with this?  It helps by letting you give
the game program more or less exclusive access to a given core, so
that Windows won't have to accommodate other program threads running on
the same core.  Keeping a given core free of non-game threads makes it
more likely that the core will be free for the game's use whenever the
game is ready to do a little bit more work, such as a video update.
That in turn improves the chances that the game can complete frame
rendering in time for each video refresh and can update the physics
model in time for the next graphics render pass.

PinAffinity is designed to make it easy to achieve partitioning like
this.  First, it applies default CPU core affinities to every process
running throughout the system (system permissions permitting; some
Windows background tasks are protected against this sort of meddling
even with "Run as administrator" privileges).  Second, it lets you
designate selected programs as members of the Pinball group, and it
assigns these programs a different set of affinities.  All affinity
settings are persistent: the program continuously monitors the system
for newly created processes, and assigns each newly created process to
the designated affinity group.  There's no need to do anything
manually during normal operation - just launch the program at system
startup and leave it running in the background, and it'll take care of
setting the desired CPU affinities as processes come and go.

## Custom configurations

Out of the box, the program has two categories, "Pinball" (for your
pinball simulators and related programs) and "Normal" (for everything else).
The Normal group is assigned core 0 and cores 4 and higher, and the Pinball
group is assigned cores 1, 2, and 3.

The default setup is really meant for 4-core system, which were the most
common gaming CPUs at the time I first wrote the program.  CPUs have been
steadily adding more cores since then, so you'll probably want to customize
the configuration to better match your specific CPU.  You can do this by
editing the file `AffinityTypes.txt`, found in the program install folder.

`AffinityType.txt` also lets you create your own custom program categories
beyond the "Pinball" and "Normal" groups.  This might be useful if you're
running multiple pinball simulators that have different threading characteristics.
It can be counterproductive to assign *too many* cores to a pinball program,
since any cores that the program can't take advantage of could be used by
background tasks instead.

The `AffinityType.txt` file has extensive comments at the top of the
file that explain the syntax, both for assigning CPU cores and for
creating new custom categories.  As you might well expect from
experience with virtually any other Windows programs, any changes you
make to `AffinityType.txt` won't take effect until you restart
PinAffinity.

I know of no general or theoretical way to estimate the ideal number
of cores to assign to a given program.  That's a function of the
program's architecture and numerous minute details of its
implementation, and probably even depends on the details of your
system hardware.  The best guidance I can give you is to experiment
with different settings and see what works best for your setup.  For
older systems with only 4 cores, it seemed to work best to assign
three of the four cores to the Pinball group, and reserve one core
for everything else.  For newer systems with 8 or 12 or 16 cores,
I'd probably start by going half and half - assign half the cores
to the Pinball group, and the other half to everything else.  Then
experiment with moving a few cores to one side or the other and see
if it makes any difference.
