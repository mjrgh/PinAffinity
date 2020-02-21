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
