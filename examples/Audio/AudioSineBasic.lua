#!/usr/bin/env luajit

--[[----------------------------------------------------------
  Audio Sine Synthesis

    [made after JUCE's audio tutorials]
    [http://learn.juce.com/tutorials]

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

]]------------------------------------------------------------



local title = "Audio Sine"
local app, luce = require"luce.LApplication"(title, ...)

local function MainWindow(args)
    local app, luce = app or _G.App, luce or _G.Luce
    local wsize     = {600,100}
    local mc = luce:MainComponent("MainComponent")
    local documentWindow = luce:Document(title)
    
    local audio = luce:AudioAppComponent("audio")
    audio:setAudioChannels(0, 1) -- 0 input, 1 output

    local double_Pi = math.pi*2

    local currentSampleRate, currentAngle, angleDelta = 0,0,0

    local freq = luce:Slider("frequency")
    freq:setRange(50.0, 5000.0)
    freq:setSkewFactorFromMidPoint(500.0);
    local function updateAngleDelta()
        local cyclesPerSample = freq.value / currentSampleRate
        angleDelta = cyclesPerSample * 2.0 * double_Pi
    end
    freq:valueChanged(function()
        if(currentSampleRate>0)then updateAngleDelta() end
    end)

    audio:prepareToPlay(function(_, sampleRate)
        currentSampleRate = sampleRate
        updateAngleDelta()
    end)
    
    local level = 0.125
    local sin = math.sin
    audio:getNextAudioBlock(function(startSample, numSamples, numChannels, audioSampleBuffer)
        local sin = sin
        local buffer = {}
        for sample = 1, numSamples do
            local currentSample = sin(currentAngle)
            currentAngle = currentAngle + angleDelta
            buffer[sample] = currentSample * level
        end
        audioSampleBuffer:setData(0, 0, buffer)
    end)

    app:initialised(function()
        audio:start()
    end)
    app:shutdown(function()
        audio:close()
    end)

    mc:resized(function()
        local w = mc:getWidth()-20
        freq.bounds = {10, 10, w, 20}
    end)
    --
    documentWindow:setBackgroundColour( luce.Colours.peru )
    
    ---
    mc:setSize(wsize)
    mc:addAndMakeVisible(audio)
    mc:addAndMakeVisible(freq)
    documentWindow:setContentOwned( mc, true )
    documentWindow:setSize(wsize)
    documentWindow:setVisible(true)
    return documentWindow
end

local function control()
end
return app:start(MainWindow) --, control)
