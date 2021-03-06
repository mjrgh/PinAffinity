PinAffinity:  A simplified CPU affinity tool for virtual pin cabs

Copyright 2018 Michael J Roberts.  
Distributed under the MIT License (see License.txt).


1. HOW TO INSTALL

Unzip the files into a folder on your hard disk.  The program is
self-contained and only uses files its own folder.

(Don't put it within Program Files, though.  The program writes files
in its own folder to save settings, and Windows doesn't allow this if
it's located within the Program Files directory tree.)

2.  BASIC USE

The program is set up to work out of the box for Visual Pinball and
related software.  Just launch the program and leave it running in the
background while you run games in VP.

When you open the PinAffinity window, you'll notice several programs
listed at the top, with "Pinball" listed in the Type column.  Those
are the pinball programs that get special CPU core assignments.  If
you're using any Visual Pinball versions not already listed, follow
these steps:

* Select Program > Add Program... from the main menu

* Navigate to the .EXE for your program and click Open

* The program will now appear in the process list even if it's
  not running.  Right click the program and select 
  Set CPU Affinity Type > Pinball on the menu.

The first time you run the program, you should test that it's working
as follows.  Launch Visual Pinball and start playing a game.  With the
game still running, switch back to the PinAffinity window.  Look for
the Visual Pinball executable in the PinAffinity process list, e.g.,
VPinballX.exe if you're running VP 10.  Make sure that the Affinity
column shows something like "-+++".  If it says "Unable", it means
that Windows blocked the affinity change because of user privilege
restrictions.  You can get around this by exiting out of PinAffinity
and re-launching it in Administrator mode, by right-clicking on the
.exe file icon and selecting "Run as Administrator" from the menu.
You'll probably want to run in Administrator mode anyway for routine
use, because it allows the program to set affinities for the
miscellaneous Windows background tasks that are always running.  Those
tasks wake up at random times to do system chores, so it further helps
VP performance to include them in the affinity settings and thereby
keep them off the cores that VP is using.

When you're running games, you should leave the PinAffinity program
running, but it's best to minimize it so that it doesn't have to keep
refreshing the window.  Note that the window minimizes to an icon in
the "system tray" - the little icon bar next to the Windows desktop
clock.  Just click the icon to bring the window back.

(If you don't see the icon in the tray area, it's in the "hidden"
portion of the tray.  Windows tries to reduce clutter in the tray by
hiding icons that aren't actively trying to notify you of something.
To see the hidden icons, click the little up-arrow next to the tray.
The PinAffinity icon should be in the pop-up box that appears.  If you
want the PinAffinity icon to stay visible in the main portion of the
tray, click the up-arrow and then click "Customize".  Find PinAffinity
in the list.  Change its setting to "Show icon and notifications".)

The default configuration assigns VP cores #1, #2, and #3, and assigns
the remaining cores to all other processes on the system.  This gives
VP almost exclusive access to three cores (assuming you have a 4+ core
system), which reduces preemption by background tasks.  This helps
make VP run more smoothly because it reduces the chance that VP will
be interrupted at a critical moment when it has to update the physics
or graphics rendering to keep up with real-time game action.  See
"THEORY" below for more on why this helps.


3. AUTOMATIC LAUNCH AT STARTUP

You'll probably also want to set up the program to launch each time
you restart Windows so that it's always running while you play.

The easiest way is to create a shortcut to the PinAffinity.exe file
in your Start Menu > Programs > Startup folder.  After creating the
shortcut, right-click it and open its Properties dialog, then select
"Run: Minimized" in the Shortcut tab.  This will start it with its
window minimized.  However, this won't launch in Administrator mode,
which you'll probably want to do.

Setting up automatic launch in Administrator mode is a little more
work, but not too hard:

* Run Windows Task Scheduler (use Windows+S to search for it)

* Click Create Task in the Actions pane

* On the General tab, enter a name (say, "Run PinAffinity")

* !!! Click the box "Run with the highest privileges" !!!

* On the Triggers tab, click New

* In the "Begin the task" drop-down at the top, select 
  "At log on"

* Click OK

* On the Actions tab, click New

* Click Browse and select PinAffinity.exe

* In the "Add arguments" box, type /MINIMIZE

* Click OK

* Click OK in the main dialog 

The step marked !!! is the crucial one for making sure the program
runs with Administrator privileges.  Of course, your user account must
actually be an Administrator account for this to work, meaning you set
it up in the Administrators group.  If you're using a limited user
account, the "highest privileges" available will be standard user
level privileges, so there's no benefit to using this more complicated
approach; you might as well just set up the Startup shortcut as
described earlier.



4. WHEN NOT TO USE PINAFFINITY

You might want to close PinAffinity when using your cab PC for major
tasks other than playing pinball.  PinAffinity reserves CPU resources
for VP, which means it takes those resources away from other programs.
There's no benefit when you're not pinballing, and it can make other
programs feel sluggish because they're confined to one CPU core.

To restore everything to its original CPU usage, simply quit out of
PinAffinity.  The program restores all of the original settings when
it exits, so your system will be back to normal.  You can always start
it up again when you're ready to go back to pinball playing.


5. MORE DETAILS

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
entry.  After you add a program, it will appear in the list even
though it's not running.  You can now right-click the program and
select Set CPU Affinity Type to select its program group.


6. ADVANCED CONFIGURATION

One of the design goals for this project was to keep it really simple,
which is why you don't see any dialogs full of "Core #0 ... Core #63"
checkboxes like you would in a more full-featured Task Manager type of
tool.  The factory settings just give you two program "Types" that you
can set - Normal and Pinball.  The CPU affinities of a program are
determined by the type you assign, so you don't have to mess with
individual core assignments.

Based on my own experience, this simple partitioning is all you need
on a pin cab to get some significant performance improvements out of
VP.  But I did make a small provision for more customized setups.  You
can create your own custom affinity types, or change the standard
types, but not through the UI.  You have to edit the text file
AffinityTypes.txt (in the PinAffinity program folder).  This contains
a list of the CPU affinity types available in the program.  The types
are listed one per line; each entry has a name, which is used for
display purposes, and an affinity mask, separated by a colon (:).

The affinity mask is a 64-bit hex value.  The least significant bit
represents CPU #0.  For example, the mask 000000000000000F enables
CPUs #0, 1, 2, and 3, because bits 0, 1, 2, and 3 are set to '1' and
all other bits are set to '0'.

This defines a type called "Normal" and sets it to use CPU #0 only:

   Normal:0000000000000001

The first entry in the file is always the default.  The default is
what's used for processes that aren't explicitly assigned other Type
settings.  The name of this first entry isn't important; all that
matters is its position as the first entry.  You can call it "Super
Special Rare Unique Definitely Non-Default Process Type" and it'll
still be the default as long as it's the first entry.

After editing this file, you'll have to close and re-launch the
program for the new settings to take effect.

The factory settings are as follows:

    Normal:FFFFFFFFFFFFFFF1
    Pinball:000000000000000E

That assigns cores #1, 2, and 3 to designated Pinball programs and all
of the other cores to all other programs.  These settings were chosen
because they scale naturally to 2-, 4-, and 8-core systems.  There's
more on this under THEORY below.


7. THEORY

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

Note that this might not be the ideal layout for hyperthreaded
processors.  Hyperthreaded CPUs show up in Windows as having twice as
many "logical" (read: imaginary) cores as the chip actually has
physical cores.  For example, my desktop's i7-3770 appears to have 8
cores in Windows, even though it's physically a quad-core chip.
That's because each physical core appears as two logical cores.
Windows groups the logical pairs in its CPU numbering, so what Windows
calls logical cores 0 and 1 are the first physical core in the CPU,
logical cores 2-3 and the second physical core, and so on.  

The big complication with hyperthreading is that it doesn't give you
true, general-purpose concurrent execution on each logical pair; it
gives you opportunistic concurrency that depends on how the
instructions on the paired virtual cores happen to use the subunits
within the core.  Some types of paired threads work well together to
achieve a very high degree of true concurrency, and some clash to such
an extent that they don't see any speedup from the extra logical core.
Gamers generally consider hyperthreading to be a negative because of
this unpredictability.  For VP, the best approach might be to take the
logical cores out of the mix and use only the true cores.  So on a
quad-core-with-hyperthreading CPU, we might do this:

   Normal:03
   Pinball:54

That assigns cores 0 and 1 to default processes, and assigns cores 2,
4, and 6 to Pinball, leaving cores 3, 5, and 7 unused.  It might seem
counterproductive to essentially disable half the logical cores, but
we're still using all of the physical cores, and we're doing so in
such a way that each thread gets to run at full speed on the physical
core it's assigned to, because there's less chance that a clashing
thread can be scheduled on the logical core counterpart.  That might
actually speed up the individual threads vs sharing logical pairs.
Remember that stutter reduction is all about optimizing for real-time
response, whereas hyperthreading's goal is to increase overall
throughput, which can come at the expense of individual thread speed.


8. HOW MANY CORES DOES VP ACTUALLY NEED?

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


9. IF YOU NEED SOMETHING MORE POWERFUL...

PinAffinity is meant to be a simple tool to solve a specific problem.
It's not a fully general CPU affinity tool, let alone a Task
Manager replacement.  If you're looking for something more powerful,
here are a couple of suggestions:

* SysInternals Process Explorer

* Process Hacker 3

Both of those are full Task Manager replacements with many advanced
features.
