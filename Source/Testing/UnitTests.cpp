/*
  ==============================================================================

    UnitTests.cpp
    Created: 5 May 2023 12:36:27pm
    Author:  Andy Truss

  ==============================================================================
*/

#include "UnitTests.h"

//TEST_CASE("Plugin instance name", "[name]")
//{
//    testPluginProcessor = new AudioPluginAudioProcessor();
//    CHECK_THAT(testPluginProcessor->getName().toStdString(),
//               Catch::Matchers::Equals("Filter Unit Test"));
//    delete testPluginProcessor;
//}

//TEST_CASE("Read and write buffer", "[dummy]")
//{
//    juce::AudioBuffer<float> *buffer = Helpers::generateAudioSampleBuffer();
//    Helpers::writeBufferToFile(buffer, "test_file");
//    juce::AudioBuffer<float> *readBuffer = Helpers::readBufferFromFile("test_file");
//    CHECK_THAT(*buffer,
//               AudioBuffersMatch(*readBuffer));
//    juce::File test_file ("test_file");
//    test_file.deleteFile();
//}
//
//TEST_CASE("Filter", "[functionality]")
//{
//    int samplesPerBlock = 4096;
//    int sampleRate = 44100;
//
//    testPluginProcessor = new AudioPluginAudioProcessor();
//
//    //Helper to read a sine sweep wav
//    juce::MemoryMappedAudioFormatReader *reader = Helpers::readSineSweep();
//    juce::AudioBuffer<float> *buffer = new juce::AudioBuffer<float>(reader->numChannels, reader->lengthInSamples);
//    reader->read(buffer->getArrayOfWritePointers(), 1, 0, reader->lengthInSamples);
//
//    juce::AudioBuffer<float> originalBuffer(*buffer);
//
//    int chunkAmount = buffer->getNumSamples() / samplesPerBlock;
//
//    juce::MidiBuffer midiBuffer;
//
//    testPluginProcessor->prepareToPlay(sampleRate, samplesPerBlock);
//
//    for (int i = 0; i < chunkAmount; i++) {
//        juce::AudioBuffer<float> processBuffer(buffer->getNumChannels(), samplesPerBlock);
//        for (int ch = 0; ch < buffer->getNumChannels(); ++ch) {
//            processBuffer.copyFrom(0, 0, *buffer, ch, i * samplesPerBlock, samplesPerBlock);
//        }
//
//        testPluginProcessor->processBlock(processBuffer, midiBuffer);
//        for (int ch = 0; ch < buffer->getNumChannels(); ++ch) {
//            buffer->copyFrom(0, i * samplesPerBlock, processBuffer, ch, 0, samplesPerBlock);
//        }
//    }
//
//    //Check that originalBuffer has higher total energy
//    CHECK_THAT(originalBuffer,
//               !AudioBufferHigherEnergy(*buffer));
//
//    juce::Array<float> maxEnergies;
//    for (int i = 0; i < fft_size / 2; i++) {
//        //Set the threshold to some value for the lowest 32 frequency bands
//        if (i < 32) {
//            maxEnergies.set(i, 100);
//        }
//        //Skip the rest
//        else {
//            maxEnergies.set(i, -1);
//
//        }
//    }
//    //Check that lower end frequencies are within limits
//    CHECK_THAT(*buffer,
//               AudioBufferCheckMaxEnergy(maxEnergies));
//
//    delete buffer;
//    delete reader;
//    delete testPluginProcessor;
//}
//TEST_CASE("Wet Parameter", "[parameters]")
//{
//    testPluginProcessor = new AudioPluginAudioProcessor();
//    //Helper to generate a buffer filled with noise
//    juce::AudioBuffer<float> *buffer = Helpers::generateAudioSampleBuffer();
//    juce::AudioBuffer<float> originalBuffer(*buffer);
//
//    juce::MidiBuffer midiBuffer;
//
//    testPluginProcessor->prepareToPlay(44100, 4096);
//    testPluginProcessor->processBlock(*buffer, midiBuffer);
//
//    //Check that initial value of wet is not zero, i.e. filtering happens
//    CHECK_THAT(*buffer,
//               !AudioBuffersMatch(originalBuffer));
//
//    delete buffer;
//
//    buffer = Helpers::generateAudioSampleBuffer();
//
//    //Get and set parameter
//    auto *parameters = testPluginProcessor->getParameters();
//    juce::RangedAudioParameter* pParam = parameters->getParameter ( "WET"  );
//    pParam->setValueNotifyingHost( 0.0f );
//
//    for (int ch = 0; ch < buffer->getNumChannels(); ++ch)
//        originalBuffer.copyFrom (ch, 0, *buffer, ch, 0, buffer->getNumSamples());
//    testPluginProcessor->processBlock(*buffer, midiBuffer);
//
//    //Check that filter now doesnt affect the audio signal
//    CHECK_THAT(*buffer,
//               AudioBuffersMatch(originalBuffer));
//
//    delete buffer;
//
//    buffer = Helpers::generateAudioSampleBuffer();
//    pParam->setValueNotifyingHost( 1.0f );
//
//
//    for (int ch = 0; ch < buffer->getNumChannels(); ++ch)
//        originalBuffer.copyFrom (ch, 0, *buffer, ch, 0, buffer->getNumSamples());
//    testPluginProcessor->processBlock(*buffer, midiBuffer);
//
//
//    CHECK_THAT(*buffer,
//               !AudioBuffersMatch(originalBuffer));
//
//    delete buffer;
//    delete testPluginProcessor;
//}

