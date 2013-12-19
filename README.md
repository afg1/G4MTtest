G4MTtest
========

Test code for geant4 MT. Designed for use with Geant4.10, will NOT work with beta versions or older. Also won't work
unless you have built Geant4.10 with multithreading support.

Compilation is done by running cmake on the source directory (you can do this from a build directory to keep build files separate)
and then running make. This will produce the executable, which is called MFT. The executable name can be changed in 
CMakeLists.txt if you wish.

To see what arguments are needed for the program, run it with the argument 'h' like so:

./MFT h

You should get:

Help for ./MFT
Argument 1:	Name of a macro file to run
Argument 2:	Path to put output
Argument 3:	Number of threads to use (default 4)

At present, I haven't figured out all the arguments that can go in the macro file, but running ./MFT with no arguments
and browsing the help within Geant4 should give you an idea.

The default simulation is of 177MeV protons into water, with the initial position at (0,0,0) and the direction a unit
vector along (1,0,0). These can all be changed within the macro, but I'm not sure of the commands needed. 

Output is saved wherever you tell it to be put, I reccomend a clean directory to put everything in, since the pyton scripts
will combine an entore directory's worth of files that fit the right regex. Output is directly generated as numpy compatible
2d histograms, which can be read in and displayed as shown in the PlotHist.py file. Bin edges and sensible axes labels
are provided by the header fie which is also written by MFT.

The number of threads used is the final argument, and will default to 4, setting it to 1 will git you effectively
single threaded execution, but it might be a bit different to a serial program written with old-school Geant4. 

Finally, I haven't worked out how to shut it up, so it is a good idea to redirect all output to /dev/null if you're
doing a proper run.
