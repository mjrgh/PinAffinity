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
threads.  It's not a matter of saturating a CPU; what matter is
latency.  Video game software requires near instantaneous scheduling
to keep graphics rendering and physics model evolution in sync with
real time.  Reserving one or more cores for exclusive use by gaming
threads can greatly improve the chances that a core is free to be
scheduled immediately whenever a game thread has work to do.  That in
turn improves the chances that the game can complete frame rendering
in time for each video refresh and can update the physics model in
time for the next graphics render pass.

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
