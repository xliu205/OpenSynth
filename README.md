# OpenSynth

CS32 Term Project

# Dev Setup

1. Download JUCE framework from https://juce.com/get-juce/. Unpack the folder and move it to your home directory. Also download XCode or Visual Studio.
2. Clone this repo into your cs32 projects folder
3. Inside the project directory, open "OpenSynth.jucer". Then, press "Save and open in IDE" near the top of the window. This will export the JUCE project to your IDE

- NOTE: If you installed JUCE to a different location on your computer, you may need to reconfigure the location of your modules in the Projucer settings.

# Warning

From the JUCE tutorials:

"You should never add, rename, and/or remove source files from JUCE projects inside your native IDE (such as Xcode, Visual Studio). These changes would be overwritten the next time you save the project in Projucer (which re-generates the native IDE projects every time). Instead, always use the Projucer itself to make such changes."

For information on adding, renaming, and removing files, see the project management tutorial here: https://docs.juce.com/master/tutorial_manage_projucer_project.html

# Week 2 Progress Update

Week 2 Progress Update
Xingyu Liu (xliu205), Karma Selsey (kselsey), Andrew Truss (atruss1), Makayla McPherson (mmcpher1)
This week we were able to get working prototypes of the UI and synth engine. Much of our time early on was spent familiarizing ourselves with the JUCE framework and its modules, which contain a wealth of classes for synth objects like filters and envelopes, as well as signal processing utilities for creating more advanced functionality. Currently, our project has three main parts: The Plugin Processor, Plugin Editor, and synth classes. The Plugin Processor handles midi and audio input/output from the host application and interacts directly with the audio buffer. The Editor is essentially our frontend. It defines all the UI elements and contains the listeners that allow those elements to communicate with the Processor. SynthSound.h and SynthVoice.h define the classes representing the oscillators and synth voices. Our current demo is monophonic, but defining the synth in terms of instances of a SynthVoice class will allow for multiple voices to be rendered in the future, enabling polyphony.
Currently, our UI is just a rough proof of concept for the controls that a single oscillator module will have in the final product. We have not integrated the Editor and Processor yet but are working on doing so now, and do not expect much difficulty. Although the synth currently has very few features, we expect that implementing the filters, waveshaping, and envelopes will be fairly straightforward now that we’ve gotten comfortable using C++ with JUCE. Our main concerns are:

1. Implementing our proposed modulation scheme. We initially planned to allow modulation sources to modify any parameter, including other modulation sources. However, this may prove difficult as we did not create a clear-enough vision of how this system would actually behave.
2. We have not started testing, even though there are C++ testing libraries that come packaged with JUCE. We plan to have unit tests written for our current implementation in the next few days, but we are behind schedule in this area. Because JUCE is largely geared towards amateur musician-programmers, their tutorials emphasize debugging by actually running the plugin, either in a DAW or their own mock host application. We have largely been using this approach to verify that our implementation is working as intended, but extensive testing is needed.
