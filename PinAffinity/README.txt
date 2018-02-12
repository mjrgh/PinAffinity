PinAffinity:  A simplified CPU affinity tool for virtual pin cabs

Copyright 2018 Michael J Roberts.  
Distributed under the MIT License (see License.txt).


1. HOW TO INSTALL

Unzip the files into a folder on your hard disk.  The program is
self-contained and only uses files its own folder.

(Don't put it within Program Files, though.  The program writes files
in its own folder to save settings, and Windows doesn't allow this if
it's located within the Program Files directory tree.)

For automatic startup, create a shortcut to the .exe file in your
Startup folder.  I recommend setting it to start in "Minimized" mode
("Run: Minimized" on the Shortcut tab of the Properties window for the
shortcut).

You might also want to set "Run as Administrator" mode (click the
Advanced button on the Properties window Shortcut tab.)  That allows
PinAffinity to set affinities for most of the Windows system
background tasks.


2.  BASIC USE

The program is set up to work out of the box for Visual Pinball and
related software.  Just launch the program and leave it running in the
background (with the window minimized) while you use VP.

The default configuration assigns VP cores #1, #2, and #3, and assigns
the remaining cores to all other processes on the system.  This gives
VP almost exclusive access to three cores (if you have a 4-core
system), which reduces preemption by background tasks.  This helps
make VP run more smoothly because it reduces the chance that VP will
be interrupted at a critical moment when it has to update the physics
or graphics rendering to keep up with real-time game action.  See
"THEORY" below for more on why this helps.

Note that the window minimizes to an icon the "system tray" - that's
the little icon bar next to the clock, usually in the lower right
corner of your monitor.  To bring the program window back, just click
the tray icon.


3. WHEN NOT TO USE IT

You might want to close PinAffinity when using your cab PC for major
tasks other than playing pinball.  PinAffinity reserves CPU resources
for VP, which means it takes those resources away from other programs.
There's no benefit when you're not pinballing, and it can make other
programs feel sluggish because they're confined to one CPU core.

To restore everything to its original CPU usage, simply quit out of
PinAffinity.  The program restores all of the original settings when
it exits, so your system will be back to normal.  You can always start
it up again when you're ready to go back to pinball playing.


4.  CUSTOMIZING IT

The main UI window shows a list of all running processes, similar
to the Task Manager "Details" list.  There are two columns that
won't look familiar from Task Manager, though:

* "Type" is the affinity group type.  All programs that aren't
  specially designated as Pinball software have the Normal type,
  which is the default.  All of the Windows background processes
  and any other apps you're running will be shown with Normal
  type.

* "CPU Affinity" shows the list of CPUs that each task is assigned
  to.  A "+" sign means the process can use that core, a "-" sign
  means it can't use that core.  Cores are listed from Core #0 at
  the left.  For example, -+------ means that a program is assigned
  to Core #1 only.  Note that the list will show the number of
  cores actually available in your system, so if you have an i5
  with four cores, it'll look like -+--.

  If the CPU Affinity column shows "Unable", it means that Windows
  didn't allow PinAffinity to modify that process's settings.
  Windows normally prohibits access to processes started by Windows
  itself or by another user.  PinAffinity can control most of
  these other processes as well if you use "Run As Administrator"
  when launching the program.


The CPU Affinity settings for each program are determined by the
Type setting for the program.  You can set each program's type
by right-clicking on the program, selecting Set CPU Affinity Type,
and selecting the desired type from the drop list.  "Normal" is
the default for any program you don't specifically set.

Programs listed with no PID or Status aren't actually running.  These
represent programs that have been explicitly designated as non-default
affinity types.  PinAffinity will automatically set the configured
affinity for any new instance of that program as soon as it starts.

You can add new items to the "saved" program list even if they're
not currently running.  Click Program > Add Program..., then select
the application .EXE file for the program you want to add.  Note
that only the name of the executable is stored, not the path, so
copies of the same file from any folder will be covered by one
entry.


5. ADVANCED CONFIGURATION

You can create your own custom affinity types, or change the standard
types, but not through the UI.  You have to edit the text file
AffinityTypes.txt (in the PinAffinity program folder).  This contains
a list of the CPU affinity types available in the program.  The types
are listed one per line; each entry has a name, which is used for
display purposes, and an affinity mask, separated by a colon (:).  The
affinity mask is a 64-bit hex value.  The least significant bit
represents CPU #0.  For example, the mask 000000000000000F enables
CPUs #0, 1, 2, and 3, because bits 0, 1, 2, and 3 are set to '1' and
all other bits are set to '0'.

   Normal:0000000000000001

That sets the standard "Normal" entry, which assigns all processes not
otherwise configured to CPU #0 only.

The first entry is always the default for processes that don't have
other settings.  

After editing this file, you'll have to close and re-launch the
program for the new settings to take effect.


6. THEORY

Virtual pinball is fundamentally a video game, which creates some
special performance needs.  The main one is real-time execution: the
pinball simulator has to be able to do its computing work at almost
exactly the same time as the simulated events are occurring, so that
the on-screen motion looks realistic.  The Windows multi-tasking
scheduler normally optimizes for overall system throughput, and tries
to balance the load so that programs share the CPU equally over time,
which means that programs have to wait their turns while other things
are running.  This is good for general desktop computing, but not
ideal for gaming, because a game that has to wait its turn for CPU
time might sometimes have to sit out one or two video refresh cycles
of rendering time, which shows up on the screen as momentary freeze
frames that the eye perceives as "stutter".  It can also cause
unevenness in the internal physics model updates, which can make
the motion of simulated objects look less realistic.

Windows has the ability to let users override some of the default
settings for process scheduling.  One thing it lets you modify is the
"CPU Affinity" for each running program.  If you have a multi-core
process, such as an Intel i5 with 4 CPUs, Windows normally divvies
up time on the cores evenly among all programs.  CPU Affinity lets
you override this, telling Windows that it should only run program A
on core #0, program B on core #1, and so on.  Since program B is
assigned to a different core from program A, program B will never
be able to interrupt program A.  

You'll obviously have many more programs running than cores, so you
can't just extend this idea to the logical limit by assigning every
program to its own exclusive core.  It would be great if you could,
but you probably only have 4 or 8 cores and maybe 50 running processes
even on a very stripped-down and optimized Windows gaming system.
So some programs will still have to share cores.  But that's okay,
because we don't care about real-time performance for 48 of those
background tasks - we only care about real-time performance for the
pinball software!  

So here's what we want to do: corral all of the miscellaneous Windows
background tasks to one set of cores, and give the pinball software
exclusive access to the rest of the cores.  When you're running a
pinball simulation, you really don't care about performance of those
background tasks at all, so that "one set of cores" for the
miscellaneous tasks can be reduced to a single core.  That gives you
all of the rest of the system - 3 or 7 cores, depending on your CPU -
for exclusive use by the pinball software.


7. HOW MANY CORES DOES VP ACTUALLY NEED?

You might have read that Visual Pinball is single-threaded, so it
might not seem necessary to give it more than one core to itself.
But, alas, like most Internet facts, this one isn't quite true.

It's accurate to say that VP's physics and rendering are
single-threaded.  But VP also calls upon a bunch of other subsystems
that do create threads.  VPinMAME runs on a separate thread, and DOF
creates separate threads for individual output devices.  The Windows
DirectSound and DirectInput subsystems creates their own threads as
well (two to three apiece, typically), and the Direct3D drivers for
graphics cards also create threads (the AMD drivers on my desktop PC
create about 20 of them).  If you look at VP with, say, SysInternals
Process Explorer, you'll see that it has numerous threads running
during play, thanks to all of these services it calls upon.

Of these, the ones that really matter for real-time response are the
main VP thread and the VPinMAME thread.  The others, collectively, use
very little CPU time.  The DirectSound and DirectInput threads are
real-time event handlers, but they do very little computing work;
they're just there to wake up and do some small amount of work when
certain events happen.  So they don't need whole cores to themselves
by any means, but they do benefit from being on lightly loaded cores
so that they can be scheduled immediately when an event requiring
their attention occurs.

Taking all of this into account, my estimation of the ideal allocation
of resources for VP is that you should give it three cores.  This will
let the VP physics and rendering engines have cores to themselves, and
will let all of the service threads share another thread.  PinAffinity
only lets you allocate cores at the process level, so it doesn't give
you the tools to divvy up cores to the individual threads in the way
I'm suggesting.  (Windows itself has such tools at a low level, so VP
could be enhanced to take advantage of them, but it's not a suitable
function for an external tool like PinAffinity.)  Even so, the mere
act of giving three cores to VP should have the practical effect of
dividing work as I'm proposing, at least most of the time, because the
Windows scheduler will naturally assign the threads on an available
basis.  The main VP and VPM threads run almost continuously, so this
should naturally tend to keep them on separate cores given that no one
else is trying to use them most of the time.  That will leave a third
core for Windows to assign the lesser threads to whenever they wake up
briefly.

The default configuration file packaged with the program is set up
this way.  It gives cores #1, #2, and #3 to VP.  All other cores are
assigned to the "Normal" profile for everything else in the system.
I chose this arrangement because it scales nicely to systems with
different numbers of cores:

- On a dual-core system, VP gets core #1 and everything else runs
  on core #0.  The system will ignore the core #2 and #3 assignments
  for VP because it ignores cores that don't exist.  This doesn't
  give VP the three-core configuration I think is optimal, but
  that's obviously impossible on a two-core system, and this split
  into "VP" and "everything else" still gives VP the best chance
  at having one core's undivided attention.

- On a four-core system, VP gets cores 1-2-3 and everything else
  runs on core #0.

- On an 8+ core system, VP gets cores 1-2-3 and everything else
  shares the other 5+ cores.  I don't think there's much benefit
  to giving VP more than 3 cores, and this leaves plenty of CPU
  resources for other programs.  You can thus probably leave 
  PinAffinity running on an 8+ core system even when doing non-
  pinball tasks.


8. IF YOU NEED SOMETHING MORE POWERFUL...

PinAffinity is meant to be a simple tool to solve a specific problem.
It's not a fully general CPU affinity tool, let alone a Task
Manager replacement.  If you're looking for something more powerful,
here are a couple of suggestions:

* SysInternals Process Explorer

* Process Hacker 3

Both of those are full Task Manager replacements with many advanced
features.
