/*!
*  @file       MIDI.h
*  Project     Arduino MIDI Library
*  @brief      MIDI Library for the Arduino
*  @version    4.2
*  @author     Francois Best
*  @date       24/02/11
*  @license    GPL v3.0 - Copyright Forty Seven Effects 2014
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/*!
*  @file       midi_Defs.h
*  Project     Arduino MIDI Library
*  @brief      MIDI Library for the Arduino - Definitions
*  @version    4.2
*  @author     Francois Best
*  @date       24/02/11
*  @license    GPL v3.0 - Copyright Forty Seven Effects 2014
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/*!
*  @file       midi_Namespace.h
*  Project     Arduino MIDI Library
*  @brief      MIDI Library for the Arduino - Namespace declaration
*  @version    4.2
*  @author     Francois Best
*  @date       24/02/11
*  @license    GPL v3.0 - Copyright Forty Seven Effects 2014
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define MIDI_NAMESPACE                  midi
#define BEGIN_MIDI_NAMESPACE            namespace MIDI_NAMESPACE {
#define END_MIDI_NAMESPACE              }

#define USING_NAMESPACE_MIDI            using namespace MIDI_NAMESPACE;

BEGIN_MIDI_NAMESPACE

END_MIDI_NAMESPACE


#if ARDUINO
#include <Arduino.h>
#else
#include <inttypes.h>
typedef uint8_t byte;
#endif

BEGIN_MIDI_NAMESPACE

// -----------------------------------------------------------------------------

#define MIDI_CHANNEL_OMNI       0
#define MIDI_CHANNEL_OFF        17 // and over

#define MIDI_PITCHBEND_MIN      -8192
#define MIDI_PITCHBEND_MAX      8191

// -----------------------------------------------------------------------------
// Type definitions

typedef byte StatusByte;
typedef byte DataByte;
typedef byte Channel;
typedef byte FilterMode;

// -----------------------------------------------------------------------------

/*! Enumeration of MIDI types */
enum MidiType
{
    InvalidType = 0x00,    ///< For notifying errors
    NoteOff = 0x80,    ///< Note Off
    NoteOn = 0x90,    ///< Note On
    AfterTouchPoly = 0xA0,    ///< Polyphonic AfterTouch
    ControlChange = 0xB0,    ///< Control Change / Channel Mode
    ProgramChange = 0xC0,    ///< Program Change
    AfterTouchChannel = 0xD0,    ///< Channel (monophonic) AfterTouch
    PitchBend = 0xE0,    ///< Pitch Bend
    SystemExclusive = 0xF0,    ///< System Exclusive
    TimeCodeQuarterFrame = 0xF1,    ///< System Common - MIDI Time Code Quarter Frame
    SongPosition = 0xF2,    ///< System Common - Song Position Pointer
    SongSelect = 0xF3,    ///< System Common - Song Select
    TuneRequest = 0xF6,    ///< System Common - Tune Request
    Clock = 0xF8,    ///< System Real Time - Timing Clock
    Start = 0xFA,    ///< System Real Time - Start
    Continue = 0xFB,    ///< System Real Time - Continue
    Stop = 0xFC,    ///< System Real Time - Stop
    ActiveSensing = 0xFE,    ///< System Real Time - Active Sensing
    SystemReset = 0xFF,    ///< System Real Time - System Reset
};

// -----------------------------------------------------------------------------

/*! Enumeration of Thru filter modes */
enum MidiFilterMode
{
    Off = 0,  ///< Thru disabled (nothing passes through).
    Full = 1,  ///< Fully enabled Thru (every incoming message is sent back).
    SameChannel = 2,  ///< Only the messages on the Input Channel will be sent back.
    DifferentChannel = 3,  ///< All the messages but the ones on the Input Channel will be sent back.
};

// -----------------------------------------------------------------------------

/*! \brief Enumeration of Control Change command numbers.
See the detailed controllers numbers & description here:
http://www.somascape.org/midi/tech/spec.html#ctrlnums
*/
enum MidiControlChangeNumber
{
    // High resolution Continuous Controllers MSB (+32 for LSB) ----------------
    BankSelect = 0,
    ModulationWheel = 1,
    BreathController = 2,
    // CC3 undefined
    FootController = 4,
    PortamentoTime = 5,
    DataEntry = 6,
    ChannelVolume = 7,
    Balance = 8,
    // CC9 undefined
    Pan = 10,
    ExpressionController = 11,
    EffectControl1 = 12,
    EffectControl2 = 13,
    // CC14 undefined
    // CC15 undefined
    GeneralPurposeController1 = 16,
    GeneralPurposeController2 = 17,
    GeneralPurposeController3 = 18,
    GeneralPurposeController4 = 19,

    // Switches ----------------------------------------------------------------
    Sustain = 64,
    Portamento = 65,
    Sostenuto = 66,
    SoftPedal = 67,
    Legato = 68,
    Hold = 69,

    // Low resolution continuous controllers -----------------------------------
    SoundController1 = 70,   ///< Synth: Sound Variation   FX: Exciter On/Off
    SoundController2 = 71,   ///< Synth: Harmonic Content  FX: Compressor On/Off
    SoundController3 = 72,   ///< Synth: Release Time      FX: Distortion On/Off
    SoundController4 = 73,   ///< Synth: Attack Time       FX: EQ On/Off
    SoundController5 = 74,   ///< Synth: Brightness        FX: Expander On/Off
    SoundController6 = 75,   ///< Synth: Decay Time        FX: Reverb On/Off
    SoundController7 = 76,   ///< Synth: Vibrato Rate      FX: Delay On/Off
    SoundController8 = 77,   ///< Synth: Vibrato Depth     FX: Pitch Transpose On/Off
    SoundController9 = 78,   ///< Synth: Vibrato Delay     FX: Flange/Chorus On/Off
    SoundController10 = 79,   ///< Synth: Undefined         FX: Special Effects On/Off
    GeneralPurposeController5 = 80,
    GeneralPurposeController6 = 81,
    GeneralPurposeController7 = 82,
    GeneralPurposeController8 = 83,
    PortamentoControl = 84,
    // CC85 to CC90 undefined
    Effects1 = 91,   ///< Reverb send level
    Effects2 = 92,   ///< Tremolo depth
    Effects3 = 93,   ///< Chorus send level
    Effects4 = 94,   ///< Celeste depth
    Effects5 = 95,   ///< Phaser depth

    // Channel Mode messages ---------------------------------------------------
    AllSoundOff = 120,
    ResetAllControllers = 121,
    LocalControl = 122,
    AllNotesOff = 123,
    OmniModeOff = 124,
    OmniModeOn = 125,
    MonoModeOn = 126,
    PolyModeOn = 127
};

// -----------------------------------------------------------------------------

/*! \brief Create an instance of the library attached to a serial port.
You can use HardwareSerial or SoftwareSerial for the serial port.
Example: MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, midi2);
Then call midi2.begin(), midi2.read() etc..
*/
#define MIDI_CREATE_INSTANCE(Type, SerialPort, Name)                            \
    midi::MidiInterface<Type> Name((Type&)SerialPort);

#if defined(ARDUINO_SAM_DUE) || defined(USBCON)
// Leonardo, Due and other USB boards use Serial1 by default.
#define MIDI_CREATE_DEFAULT_INSTANCE()                                      \
        MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
#else
/*! \brief Create an instance of the library with default name, serial port
and settings, for compatibility with sketches written with pre-v4.2 MIDI Lib,
or if you don't bother using custom names, serial port or settings.
*/
#define MIDI_CREATE_DEFAULT_INSTANCE()                                      \
        MIDI_CREATE_INSTANCE(HardwareSerial, Serial,  MIDI);
#endif

/*! \brief Create an instance of the library attached to a serial port with
custom settings.
@see DefaultSettings
@see MIDI_CREATE_INSTANCE
*/
#define MIDI_CREATE_CUSTOM_INSTANCE(Type, SerialPort, Name, Settings)           \
    midi::MidiInterface<Type, Settings> Name((Type&)SerialPort);

END_MIDI_NAMESPACE

/*!
*  @file       midi_Settings.h
*  Project     Arduino MIDI Library
*  @brief      MIDI Library for the Arduino - Settings
*  @version    4.2
*  @author     Francois Best
*  @date       24/02/11
*  @license    GPL v3.0 - Copyright Forty Seven Effects 2014
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#include "midi_Defs.h"

BEGIN_MIDI_NAMESPACE

/*! \brief Default Settings for the MIDI Library.

To change the default settings, don't edit them there, create a subclass and
override the values in that subclass, then use the MIDI_CREATE_CUSTOM_INSTANCE
macro to create your instance. The settings you don't override will keep their
default value. Eg:
\code{.cpp}
struct MySettings : public midi::DefaultSettings
{
static const bool UseRunningStatus = false; // Messes with my old equipment!
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial2, midi, MySettings);
\endcode
*/
struct DefaultSettings
{
    /*! Running status enables short messages when sending multiple values
    of the same type and channel.\n
    Set to 0 if you have troubles controlling your hardware.
    */
    static const bool UseRunningStatus = true;

    /* NoteOn with 0 velocity should be handled as NoteOf.\n
    Set to 1 to get NoteOff events when receiving null-velocity NoteOn messages.\n
    Set to 0 to get NoteOn  events when receiving null-velocity NoteOn messages.
    */
    static const bool HandleNullVelocityNoteOnAsNoteOff = true;

    // Setting this to 1 will make MIDI.read parse only one byte of data for each
    // call when data is available. This can speed up your application if receiving
    // a lot of traffic, but might induce MIDI Thru and treatment latency.
    static const bool Use1ByteParsing = true;

    /*! Override the default MIDI baudrate to transmit over USB serial, to
    a decoding program such as Hairless MIDI (set baudrate to 115200)\n
    http://projectgus.github.io/hairless-midiserial/
    */
    static const long BaudRate = 31250;

    /*! Maximum size of SysEx receivable. Decrease to save RAM if you don't expect
    to receive SysEx, or adjust accordingly.
    */
    static const unsigned SysExMaxSize = 128;
};

END_MIDI_NAMESPACE


/*!
*  @file       midi_Message.h
*  Project     Arduino MIDI Library
*  @brief      MIDI Library for the Arduino - Message struct definition
*  @version    4.2
*  @author     Francois Best
*  @date       11/06/14
*  @license    GPL v3.0 - Copyright Forty Seven Effects 2014
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#include "midi_Namespace.h"
//#include "midi_Defs.h"

BEGIN_MIDI_NAMESPACE

/*! The Message structure contains decoded data of a MIDI message
read from the serial port with read()
*/
template<unsigned SysExMaxSize>
struct Message
{
    /*! The maximum size for the System Exclusive array.
    */
    static const unsigned sSysExMaxSize = SysExMaxSize;

    /*! The MIDI channel on which the message was recieved.
    \n Value goes from 1 to 16.
    */
    Channel channel;

    /*! The type of the message
    (see the MidiType enum for types reference)
    */
    MidiType type;

    /*! The first data byte.
    \n Value goes from 0 to 127.
    */
    DataByte data1;

    /*! The second data byte.
    If the message is only 2 bytes long, this one is null.
    \n Value goes from 0 to 127.
    */
    DataByte data2;

    /*! System Exclusive dedicated byte array.
    \n Array length is stocked on 16 bits,
    in data1 (LSB) and data2 (MSB)
    */
    DataByte sysexArray[sSysExMaxSize];

    /*! This boolean indicates if the message is valid or not.
    There is no channel consideration here,
    validity means the message respects the MIDI norm.
    */
    bool valid;

    inline unsigned getSysExSize() const
    {
        const unsigned size = unsigned(data2) << 8 | data1;
        return size > sSysExMaxSize ? sSysExMaxSize : size;
    }
};

END_MIDI_NAMESPACE


// -----------------------------------------------------------------------------

BEGIN_MIDI_NAMESPACE

/*! \brief The main class for MIDI handling.
It is templated over the type of serial port to provide abstraction from
the hardware interface, meaning you can use HardwareSerial, SoftwareSerial
or ak47's Uart classes. The only requirement is that the class implements
the begin, read, write and available methods.
*/
template<class SerialPort, class Settings = DefaultSettings>
class MidiInterface
{
public:
    inline  MidiInterface(SerialPort& inSerial);
    inline ~MidiInterface();

public:
    void begin(Channel inChannel = 1);

    // -------------------------------------------------------------------------
    // MIDI Output

public:
    inline void sendNoteOn(DataByte inNoteNumber,
        DataByte inVelocity,
        Channel inChannel);

    inline void sendNoteOff(DataByte inNoteNumber,
        DataByte inVelocity,
        Channel inChannel);

    inline void sendProgramChange(DataByte inProgramNumber,
        Channel inChannel);

    inline void sendControlChange(DataByte inControlNumber,
        DataByte inControlValue,
        Channel inChannel);

    inline void sendPitchBend(int inPitchValue, Channel inChannel);
    inline void sendPitchBend(double inPitchValue, Channel inChannel);

    inline void sendPolyPressure(DataByte inNoteNumber,
        DataByte inPressure,
        Channel inChannel);

    inline void sendAfterTouch(DataByte inPressure,
        Channel inChannel);

    inline void sendSysEx(unsigned inLength,
        const byte* inArray,
        bool inArrayContainsBoundaries = false);

    inline void sendTimeCodeQuarterFrame(DataByte inTypeNibble,
        DataByte inValuesNibble);
    inline void sendTimeCodeQuarterFrame(DataByte inData);

    inline void sendSongPosition(unsigned inBeats);
    inline void sendSongSelect(DataByte inSongNumber);
    inline void sendTuneRequest();
    inline void sendRealTime(MidiType inType);

public:
    void send(MidiType inType,
        DataByte inData1,
        DataByte inData2,
        Channel inChannel);

    // -------------------------------------------------------------------------
    // MIDI Input

public:
    inline bool read();
    inline bool read(Channel inChannel);

public:
    inline MidiType getType() const;
    inline Channel  getChannel() const;
    inline DataByte getData1() const;
    inline DataByte getData2() const;
    inline const byte* getSysExArray() const;
    inline unsigned getSysExArrayLength() const;
    inline bool check() const;

public:
    inline Channel getInputChannel() const;
    inline void setInputChannel(Channel inChannel);

public:
    static inline MidiType getTypeFromStatusByte(byte inStatus);
    static inline Channel getChannelFromStatusByte(byte inStatus);
    static inline bool isChannelMessage(MidiType inType);


    // -------------------------------------------------------------------------
    // Input Callbacks

public:
    inline void setHandleNoteOff(void(*fptr)(byte channel, byte note, byte velocity));
    inline void setHandleNoteOn(void(*fptr)(byte channel, byte note, byte velocity));
    inline void setHandleAfterTouchPoly(void(*fptr)(byte channel, byte note, byte pressure));
    inline void setHandleControlChange(void(*fptr)(byte channel, byte number, byte value));
    inline void setHandleProgramChange(void(*fptr)(byte channel, byte number));
    inline void setHandleAfterTouchChannel(void(*fptr)(byte channel, byte pressure));
    inline void setHandlePitchBend(void(*fptr)(byte channel, int bend));
    inline void setHandleSystemExclusive(void(*fptr)(byte * array, unsigned size));
    inline void setHandleTimeCodeQuarterFrame(void(*fptr)(byte data));
    inline void setHandleSongPosition(void(*fptr)(unsigned beats));
    inline void setHandleSongSelect(void(*fptr)(byte songnumber));
    inline void setHandleTuneRequest(void(*fptr)(void));
    inline void setHandleClock(void(*fptr)(void));
    inline void setHandleStart(void(*fptr)(void));
    inline void setHandleContinue(void(*fptr)(void));
    inline void setHandleStop(void(*fptr)(void));
    inline void setHandleActiveSensing(void(*fptr)(void));
    inline void setHandleSystemReset(void(*fptr)(void));

    inline void disconnectCallbackFromType(MidiType inType);

private:
    void launchCallback();

    void(*mNoteOffCallback)(byte channel, byte note, byte velocity);
    void(*mNoteOnCallback)(byte channel, byte note, byte velocity);
    void(*mAfterTouchPolyCallback)(byte channel, byte note, byte velocity);
    void(*mControlChangeCallback)(byte channel, byte, byte);
    void(*mProgramChangeCallback)(byte channel, byte);
    void(*mAfterTouchChannelCallback)(byte channel, byte);
    void(*mPitchBendCallback)(byte channel, int);
    void(*mSystemExclusiveCallback)(byte * array, unsigned size);
    void(*mTimeCodeQuarterFrameCallback)(byte data);
    void(*mSongPositionCallback)(unsigned beats);
    void(*mSongSelectCallback)(byte songnumber);
    void(*mTuneRequestCallback)(void);
    void(*mClockCallback)(void);
    void(*mStartCallback)(void);
    void(*mContinueCallback)(void);
    void(*mStopCallback)(void);
    void(*mActiveSensingCallback)(void);
    void(*mSystemResetCallback)(void);

    // -------------------------------------------------------------------------
    // MIDI Soft Thru

public:
    inline MidiFilterMode getFilterMode() const;
    inline bool getThruState() const;

    inline void turnThruOn(MidiFilterMode inThruFilterMode = Full);
    inline void turnThruOff();
    inline void setThruFilterMode(MidiFilterMode inThruFilterMode);

private:
    void thruFilter(byte inChannel);

private:
    bool parse();
    inline void handleNullVelocityNoteOnAsNoteOff();
    inline bool inputFilter(Channel inChannel);
    inline void resetInput();

private:
    bool            mThruActivated : 1;
    MidiFilterMode  mThruFilterMode : 7;

private:
    typedef Message<Settings::SysExMaxSize> MidiMessage;

private:
    StatusByte  mRunningStatus_RX;
    StatusByte  mRunningStatus_TX;
    Channel     mInputChannel;
    byte        mPendingMessage[3];
    unsigned    mPendingMessageExpectedLenght;
    unsigned    mPendingMessageIndex;
    MidiMessage mMessage;

private:
    inline StatusByte getStatus(MidiType inType,
        Channel inChannel) const;

private:
    SerialPort& mSerial;
};

// -----------------------------------------------------------------------------

unsigned encodeSysEx(const byte* inData, byte* outSysEx, unsigned inLenght);
unsigned decodeSysEx(const byte* inSysEx, byte* outData, unsigned inLenght);

END_MIDI_NAMESPACE

// -----------------------------------------------------------------------------

/*!
*  @file       MIDI.hpp
*  Project     Arduino MIDI Library
*  @brief      MIDI Library for the Arduino - Inline implementations
*  @version    4.2
*  @author     Francois Best
*  @date       24/02/11
*  @license    GPL v3.0 - Copyright Forty Seven Effects 2014
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

BEGIN_MIDI_NAMESPACE

/// \brief Constructor for MidiInterface.
template<class SerialPort, class Settings>
inline MidiInterface<SerialPort, Settings>::MidiInterface(SerialPort& inSerial)
    : mSerial(inSerial)
{
    mNoteOffCallback = 0;
    mNoteOnCallback = 0;
    mAfterTouchPolyCallback = 0;
    mControlChangeCallback = 0;
    mProgramChangeCallback = 0;
    mAfterTouchChannelCallback = 0;
    mPitchBendCallback = 0;
    mSystemExclusiveCallback = 0;
    mTimeCodeQuarterFrameCallback = 0;
    mSongPositionCallback = 0;
    mSongSelectCallback = 0;
    mTuneRequestCallback = 0;
    mClockCallback = 0;
    mStartCallback = 0;
    mContinueCallback = 0;
    mStopCallback = 0;
    mActiveSensingCallback = 0;
    mSystemResetCallback = 0;
}

/*! \brief Destructor for MidiInterface.

This is not really useful for the Arduino, as it is never called...
*/
template<class SerialPort, class Settings>
inline MidiInterface<SerialPort, Settings>::~MidiInterface()
{
}

// -----------------------------------------------------------------------------

/*! \brief Call the begin method in the setup() function of the Arduino.

All parameters are set to their default values:
- Input channel set to 1 if no value is specified
- Full thru mirroring
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::begin(Channel inChannel)
{
    // Initialise the Serial port
#if defined(FSE_AVR)
    mSerial. template open<Settings::BaudRate>();
#else
    mSerial.begin(Settings::BaudRate);
#endif

    mInputChannel = inChannel;
    mRunningStatus_TX = InvalidType;
    mRunningStatus_RX = InvalidType;

    mPendingMessageIndex = 0;
    mPendingMessageExpectedLenght = 0;

    mMessage.valid = false;
    mMessage.type = InvalidType;
    mMessage.channel = 0;
    mMessage.data1 = 0;
    mMessage.data2 = 0;

    mThruFilterMode = Full;
    mThruActivated = true;
}

// -----------------------------------------------------------------------------
//                                 Output
// -----------------------------------------------------------------------------

/*! \addtogroup output
@{
*/

/*! \brief Generate and send a MIDI message from the values given.
\param inType    The message type (see type defines for reference)
\param inData1   The first data byte.
\param inData2   The second data byte (if the message contains only 1 data byte,
set this one to 0).
\param inChannel The output channel on which the message will be sent
(values from 1 to 16). Note: you cannot send to OMNI.

This is an internal method, use it only if you need to send raw data
from your code, at your own risks.
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::send(MidiType inType,
    DataByte inData1,
    DataByte inData2,
    Channel inChannel)
{
    // Then test if channel is valid
    if (inChannel >= MIDI_CHANNEL_OFF ||
        inChannel == MIDI_CHANNEL_OMNI ||
        inType < 0x80)
    {
        if (Settings::UseRunningStatus)
        {
            mRunningStatus_TX = InvalidType;
        }
        return; // Don't send anything
    }

    if (inType <= PitchBend)  // Channel messages
    {
        // Protection: remove MSBs on data
        inData1 &= 0x7f;
        inData2 &= 0x7f;

        const StatusByte status = getStatus(inType, inChannel);

        if (Settings::UseRunningStatus)
        {
            if (mRunningStatus_TX != status)
            {
                // New message, memorise and send header
                mRunningStatus_TX = status;
                mSerial.write(mRunningStatus_TX);
            }
        }
        else
        {
            // Don't care about running status, send the status byte.
            mSerial.write(status);
        }

        // Then send data
        mSerial.write(inData1);
        if (inType != ProgramChange && inType != AfterTouchChannel)
        {
            mSerial.write(inData2);
        }
    }
    else if (inType >= TuneRequest && inType <= SystemReset)
    {
        sendRealTime(inType); // System Real-time and 1 byte.
    }
}

// -----------------------------------------------------------------------------

/*! \brief Send a Note On message
\param inNoteNumber  Pitch value in the MIDI format (0 to 127).
\param inVelocity    Note attack velocity (0 to 127). A NoteOn with 0 velocity
is considered as a NoteOff.
\param inChannel     The channel on which the message will be sent (1 to 16).

Take a look at the values, names and frequencies of notes here:
http://www.phys.unsw.edu.au/jw/notes.html
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendNoteOn(DataByte inNoteNumber,
    DataByte inVelocity,
    Channel inChannel)
{
    send(NoteOn, inNoteNumber, inVelocity, inChannel);
}

/*! \brief Send a Note Off message
\param inNoteNumber  Pitch value in the MIDI format (0 to 127).
\param inVelocity    Release velocity (0 to 127).
\param inChannel     The channel on which the message will be sent (1 to 16).

Note: you can send NoteOn with zero velocity to make a NoteOff, this is based
on the Running Status principle, to avoid sending status messages and thus
sending only NoteOn data. sendNoteOff will always send a real NoteOff message.
Take a look at the values, names and frequencies of notes here:
http://www.phys.unsw.edu.au/jw/notes.html
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendNoteOff(DataByte inNoteNumber,
    DataByte inVelocity,
    Channel inChannel)
{
    send(NoteOff, inNoteNumber, inVelocity, inChannel);
}

/*! \brief Send a Program Change message
\param inProgramNumber The Program to select (0 to 127).
\param inChannel       The channel on which the message will be sent (1 to 16).
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendProgramChange(DataByte inProgramNumber,
    Channel inChannel)
{
    send(ProgramChange, inProgramNumber, 0, inChannel);
}

/*! \brief Send a Control Change message
\param inControlNumber The controller number (0 to 127).
\param inControlValue  The value for the specified controller (0 to 127).
\param inChannel       The channel on which the message will be sent (1 to 16).
@see MidiControlChangeNumber
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendControlChange(DataByte inControlNumber,
    DataByte inControlValue,
    Channel inChannel)
{
    send(ControlChange, inControlNumber, inControlValue, inChannel);
}

/*! \brief Send a Polyphonic AfterTouch message (applies to a specified note)
\param inNoteNumber  The note to apply AfterTouch to (0 to 127).
\param inPressure    The amount of AfterTouch to apply (0 to 127).
\param inChannel     The channel on which the message will be sent (1 to 16).
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendPolyPressure(DataByte inNoteNumber,
    DataByte inPressure,
    Channel inChannel)
{
    send(AfterTouchPoly, inNoteNumber, inPressure, inChannel);
}

/*! \brief Send a MonoPhonic AfterTouch message (applies to all notes)
\param inPressure    The amount of AfterTouch to apply to all notes.
\param inChannel     The channel on which the message will be sent (1 to 16).
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendAfterTouch(DataByte inPressure,
    Channel inChannel)
{
    send(AfterTouchChannel, inPressure, 0, inChannel);
}

/*! \brief Send a Pitch Bend message using a signed integer value.
\param inPitchValue  The amount of bend to send (in a signed integer format),
between MIDI_PITCHBEND_MIN and MIDI_PITCHBEND_MAX,
center value is 0.
\param inChannel     The channel on which the message will be sent (1 to 16).
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendPitchBend(int inPitchValue,
    Channel inChannel)
{
    const unsigned bend = inPitchValue - MIDI_PITCHBEND_MIN;
    send(PitchBend, (bend & 0x7f), (bend >> 7) & 0x7f, inChannel);
}


/*! \brief Send a Pitch Bend message using a floating point value.
\param inPitchValue  The amount of bend to send (in a floating point format),
between -1.0f (maximum downwards bend)
and +1.0f (max upwards bend), center value is 0.0f.
\param inChannel     The channel on which the message will be sent (1 to 16).
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendPitchBend(double inPitchValue,
    Channel inChannel)
{
    const int value = inPitchValue * MIDI_PITCHBEND_MAX * Settings::Toto;
    sendPitchBend(value, inChannel);
}

/*! \brief Generate and send a System Exclusive frame.
\param inLength  The size of the array to send
\param inArray   The byte array containing the data to send
\param inArrayContainsBoundaries When set to 'true', 0xf0 & 0xf7 bytes
(start & stop SysEx) will NOT be sent
(and therefore must be included in the array).
default value for ArrayContainsBoundaries is set to 'false' for compatibility
with previous versions of the library.
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendSysEx(unsigned inLength,
    const byte* inArray,
    bool inArrayContainsBoundaries)
{
    const bool writeBeginEndBytes = !inArrayContainsBoundaries;

    if (writeBeginEndBytes)
    {
        mSerial.write(0xf0);
    }

    for (unsigned i = 0; i < inLength; ++i)
    {
        mSerial.write(inArray[i]);
    }

    if (writeBeginEndBytes)
    {
        mSerial.write(0xf7);
    }

    if (Settings::UseRunningStatus)
    {
        mRunningStatus_TX = InvalidType;
    }
}

/*! \brief Send a Tune Request message.

When a MIDI unit receives this message,
it should tune its oscillators (if equipped with any).
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendTuneRequest()
{
    sendRealTime(TuneRequest);
}

/*! \brief Send a MIDI Time Code Quarter Frame.

\param inTypeNibble      MTC type
\param inValuesNibble    MTC data
See MIDI Specification for more information.
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendTimeCodeQuarterFrame(DataByte inTypeNibble,
    DataByte inValuesNibble)
{
    const byte data = (((inTypeNibble & 0x07) << 4) | (inValuesNibble & 0x0f));
    sendTimeCodeQuarterFrame(data);
}

/*! \brief Send a MIDI Time Code Quarter Frame.

See MIDI Specification for more information.
\param inData  if you want to encode directly the nibbles in your program,
you can send the byte here.
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendTimeCodeQuarterFrame(DataByte inData)
{
    mSerial.write((byte)TimeCodeQuarterFrame);
    mSerial.write(inData);

    if (Settings::UseRunningStatus)
    {
        mRunningStatus_TX = InvalidType;
    }
}

/*! \brief Send a Song Position Pointer message.
\param inBeats    The number of beats since the start of the song.
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendSongPosition(unsigned inBeats)
{
    mSerial.write((byte)SongPosition);
    mSerial.write(inBeats & 0x7f);
    mSerial.write((inBeats >> 7) & 0x7f);

    if (Settings::UseRunningStatus)
    {
        mRunningStatus_TX = InvalidType;
    }
}

/*! \brief Send a Song Select message */
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendSongSelect(DataByte inSongNumber)
{
    mSerial.write((byte)SongSelect);
    mSerial.write(inSongNumber & 0x7f);

    if (Settings::UseRunningStatus)
    {
        mRunningStatus_TX = InvalidType;
    }
}

/*! \brief Send a Real Time (one byte) message.

\param inType    The available Real Time types are:
Start, Stop, Continue, Clock, ActiveSensing and SystemReset.
You can also send a Tune Request with this method.
@see MidiType
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::sendRealTime(MidiType inType)
{
    switch (inType)
    {
    case TuneRequest: // Not really real-time, but one byte anyway.
    case Clock:
    case Start:
    case Stop:
    case Continue:
    case ActiveSensing:
    case SystemReset:
        mSerial.write((byte)inType);
        break;
    default:
        // Invalid Real Time marker
        break;
    }

    // Do not cancel Running Status for real-time messages as they can be
    // interleaved within any message. Though, TuneRequest can be sent here,
    // and as it is a System Common message, it must reset Running Status.
    if (Settings::UseRunningStatus && inType == TuneRequest)
    {
        mRunningStatus_TX = InvalidType;
    }
}

/*! @} */ // End of doc group MIDI Output

// -----------------------------------------------------------------------------

template<class SerialPort, class Settings>
StatusByte MidiInterface<SerialPort, Settings>::getStatus(MidiType inType,
    Channel inChannel) const
{
    return ((byte)inType | ((inChannel - 1) & 0x0f));
}

// -----------------------------------------------------------------------------
//                                  Input
// -----------------------------------------------------------------------------

/*! \addtogroup input
@{
*/

/*! \brief Read messages from the serial port using the main input channel.

\return True if a valid message has been stored in the structure, false if not.
A valid message is a message that matches the input channel. \n\n
If the Thru is enabled and the message matches the filter,
it is sent back on the MIDI output.
@see see setInputChannel()
*/
template<class SerialPort, class Settings>
inline bool MidiInterface<SerialPort, Settings>::read()
{
    return read(mInputChannel);
}

/*! \brief Read messages on a specified channel.
*/
template<class SerialPort, class Settings>
inline bool MidiInterface<SerialPort, Settings>::read(Channel inChannel)
{
    if (inChannel >= MIDI_CHANNEL_OFF)
        return false; // MIDI Input disabled.

    if (!parse())
        return false;

    handleNullVelocityNoteOnAsNoteOff();
    const bool channelMatch = inputFilter(inChannel);

    if (channelMatch)
    {
        launchCallback();
    }

    thruFilter(inChannel);

    return channelMatch;
}

// -----------------------------------------------------------------------------

// Private method: MIDI parser
template<class SerialPort, class Settings>
bool MidiInterface<SerialPort, Settings>::parse()
{
    if (mSerial.available() == 0)
        // No data available.
        return false;

    // Parsing algorithm:
    // Get a byte from the serial buffer.
    // If there is no pending message to be recomposed, start a new one.
    //  - Find type and channel (if pertinent)
    //  - Look for other bytes in buffer, call parser recursively,
    //    until the message is assembled or the buffer is empty.
    // Else, add the extracted byte to the pending message, and check validity.
    // When the message is done, store it.

    const byte extracted = mSerial.read();

    if (mPendingMessageIndex == 0)
    {
        // Start a new pending message
        mPendingMessage[0] = extracted;

        // Check for running status first
        if (isChannelMessage(getTypeFromStatusByte(mRunningStatus_RX)))
        {
            // Only these types allow Running Status

            // If the status byte is not received, prepend it
            // to the pending message
            if (extracted < 0x80)
            {
                mPendingMessage[0] = mRunningStatus_RX;
                mPendingMessage[1] = extracted;
                mPendingMessageIndex = 1;
            }
            // Else: well, we received another status byte,
            // so the running status does not apply here.
            // It will be updated upon completion of this message.
        }

        switch (getTypeFromStatusByte(mPendingMessage[0]))
        {
            // 1 byte messages
        case Start:
        case Continue:
        case Stop:
        case Clock:
        case ActiveSensing:
        case SystemReset:
        case TuneRequest:
            // Handle the message type directly here.
            mMessage.type = getTypeFromStatusByte(mPendingMessage[0]);
            mMessage.channel = 0;
            mMessage.data1 = 0;
            mMessage.data2 = 0;
            mMessage.valid = true;

            // \fix Running Status broken when receiving Clock messages.
            // Do not reset all input attributes, Running Status must remain unchanged.
            //resetInput();

            // We still need to reset these
            mPendingMessageIndex = 0;
            mPendingMessageExpectedLenght = 0;

            return true;
            break;

            // 2 bytes messages
        case ProgramChange:
        case AfterTouchChannel:
        case TimeCodeQuarterFrame:
        case SongSelect:
            mPendingMessageExpectedLenght = 2;
            break;

            // 3 bytes messages
        case NoteOn:
        case NoteOff:
        case ControlChange:
        case PitchBend:
        case AfterTouchPoly:
        case SongPosition:
            mPendingMessageExpectedLenght = 3;
            break;

        case SystemExclusive:
            // The message can be any lenght
            // between 3 and MidiMessage::sSysExMaxSize bytes
            mPendingMessageExpectedLenght = MidiMessage::sSysExMaxSize;
            mRunningStatus_RX = InvalidType;
            mMessage.sysexArray[0] = SystemExclusive;
            break;

        case InvalidType:
        default:
            // This is obviously wrong. Let's get the hell out'a here.
            resetInput();
            return false;
            break;
        }

        if (mPendingMessageIndex >= (mPendingMessageExpectedLenght - 1))
        {
            // Reception complete
            mMessage.type = getTypeFromStatusByte(mPendingMessage[0]);
            mMessage.channel = getChannelFromStatusByte(mPendingMessage[0]);
            mMessage.data1 = mPendingMessage[1];

            // Save data2 only if applicable
            if (mPendingMessageExpectedLenght == 3)
                mMessage.data2 = mPendingMessage[2];
            else
                mMessage.data2 = 0;

            mPendingMessageIndex = 0;
            mPendingMessageExpectedLenght = 0;
            mMessage.valid = true;
            return true;
        }
        else
        {
            // Waiting for more data
            mPendingMessageIndex++;
        }

        if (Settings::Use1ByteParsing)
        {
            // Message is not complete.
            return false;
        }
        else
        {
            // Call the parser recursively
            // to parse the rest of the message.
            return parse();
        }
    }
    else
    {
        // First, test if this is a status byte
        if (extracted >= 0x80)
        {
            // Reception of status bytes in the middle of an uncompleted message
            // are allowed only for interleaved Real Time message or EOX
            switch (extracted)
            {
            case Clock:
            case Start:
            case Continue:
            case Stop:
            case ActiveSensing:
            case SystemReset:

                // Here we will have to extract the one-byte message,
                // pass it to the structure for being read outside
                // the MIDI class, and recompose the message it was
                // interleaved into. Oh, and without killing the running status..
                // This is done by leaving the pending message as is,
                // it will be completed on next calls.

                mMessage.type = (MidiType)extracted;
                mMessage.data1 = 0;
                mMessage.data2 = 0;
                mMessage.channel = 0;
                mMessage.valid = true;
                return true;

                break;

                // End of Exclusive
            case 0xf7:
                if (mMessage.sysexArray[0] == SystemExclusive)
                {
                    // Store the last byte (EOX)
                    mMessage.sysexArray[mPendingMessageIndex++] = 0xf7;
                    mMessage.type = SystemExclusive;

                    // Get length
                    mMessage.data1 = mPendingMessageIndex & 0xff; // LSB
                    mMessage.data2 = mPendingMessageIndex >> 8;   // MSB
                    mMessage.channel = 0;
                    mMessage.valid = true;

                    resetInput();
                    return true;
                }
                else
                {
                    // Well well well.. error.
                    resetInput();
                    return false;
                }

                break;
            default:
                break;
            }
        }

        // Add extracted data byte to pending message
        if (mPendingMessage[0] == SystemExclusive)
            mMessage.sysexArray[mPendingMessageIndex] = extracted;
        else
            mPendingMessage[mPendingMessageIndex] = extracted;

        // Now we are going to check if we have reached the end of the message
        if (mPendingMessageIndex >= (mPendingMessageExpectedLenght - 1))
        {
            // "FML" case: fall down here with an overflown SysEx..
            // This means we received the last possible data byte that can fit
            // the buffer. If this happens, try increasing MidiMessage::sSysExMaxSize.
            if (mPendingMessage[0] == SystemExclusive)
            {
                resetInput();
                return false;
            }

            mMessage.type = getTypeFromStatusByte(mPendingMessage[0]);

            if (isChannelMessage(mMessage.type))
                mMessage.channel = getChannelFromStatusByte(mPendingMessage[0]);
            else
                mMessage.channel = 0;

            mMessage.data1 = mPendingMessage[1];

            // Save data2 only if applicable
            if (mPendingMessageExpectedLenght == 3)
                mMessage.data2 = mPendingMessage[2];
            else
                mMessage.data2 = 0;

            // Reset local variables
            mPendingMessageIndex = 0;
            mPendingMessageExpectedLenght = 0;

            mMessage.valid = true;

            // Activate running status (if enabled for the received type)
            switch (mMessage.type)
            {
            case NoteOff:
            case NoteOn:
            case AfterTouchPoly:
            case ControlChange:
            case ProgramChange:
            case AfterTouchChannel:
            case PitchBend:
                // Running status enabled: store it from received message
                mRunningStatus_RX = mPendingMessage[0];
                break;

            default:
                // No running status
                mRunningStatus_RX = InvalidType;
                break;
            }
            return true;
        }
        else
        {
            // Then update the index of the pending message.
            mPendingMessageIndex++;

            if (Settings::Use1ByteParsing)
            {
                // Message is not complete.
                return false;
            }
            else
            {
                // Call the parser recursively to parse the rest of the message.
                return parse();
            }
        }
    }
}

// Private method, see midi_Settings.h for documentation
template<class SerialPort, class Settings>
inline void MidiInterface<SerialPort, Settings>::handleNullVelocityNoteOnAsNoteOff()
{
    if (Settings::HandleNullVelocityNoteOnAsNoteOff &&
        getType() == NoteOn && getData2() == 0)
    {
        mMessage.type = NoteOff;
    }
}

// Private method: check if the received message is on the listened channel
template<class SerialPort, class Settings>
inline bool MidiInterface<SerialPort, Settings>::inputFilter(Channel inChannel)
{
    // This method handles recognition of channel
    // (to know if the message is destinated to the Arduino)

    if (mMessage.type == InvalidType)
        return false;

    // First, check if the received message is Channel
    if (mMessage.type >= NoteOff && mMessage.type <= PitchBend)
    {
        // Then we need to know if we listen to it
        if ((mMessage.channel == mInputChannel) ||
            (mInputChannel == MIDI_CHANNEL_OMNI))
        {
            return true;
        }
        else
        {
            // We don't listen to this channel
            return false;
        }
    }
    else
    {
        // System messages are always received
        return true;
    }
}

// Private method: reset input attributes
template<class SerialPort, class Settings>
inline void MidiInterface<SerialPort, Settings>::resetInput()
{
    mPendingMessageIndex = 0;
    mPendingMessageExpectedLenght = 0;
    mRunningStatus_RX = InvalidType;
}

// -----------------------------------------------------------------------------

/*! \brief Get the last received message's type

Returns an enumerated type. @see MidiType
*/
template<class SerialPort, class Settings>
inline MidiType MidiInterface<SerialPort, Settings>::getType() const
{
    return mMessage.type;
}

/*! \brief Get the channel of the message stored in the structure.

\return Channel range is 1 to 16.
For non-channel messages, this will return 0.
*/
template<class SerialPort, class Settings>
inline Channel MidiInterface<SerialPort, Settings>::getChannel() const
{
    return mMessage.channel;
}

/*! \brief Get the first data byte of the last received message. */
template<class SerialPort, class Settings>
inline DataByte MidiInterface<SerialPort, Settings>::getData1() const
{
    return mMessage.data1;
}

/*! \brief Get the second data byte of the last received message. */
template<class SerialPort, class Settings>
inline DataByte MidiInterface<SerialPort, Settings>::getData2() const
{
    return mMessage.data2;
}

/*! \brief Get the System Exclusive byte array.

@see getSysExArrayLength to get the array's length in bytes.
*/
template<class SerialPort, class Settings>
inline const byte* MidiInterface<SerialPort, Settings>::getSysExArray() const
{
    return mMessage.sysexArray;
}

/*! \brief Get the lenght of the System Exclusive array.

It is coded using data1 as LSB and data2 as MSB.
\return The array's length, in bytes.
*/
template<class SerialPort, class Settings>
inline unsigned MidiInterface<SerialPort, Settings>::getSysExArrayLength() const
{
    return mMessage.getSysExSize();
}

/*! \brief Check if a valid message is stored in the structure. */
template<class SerialPort, class Settings>
inline bool MidiInterface<SerialPort, Settings>::check() const
{
    return mMessage.valid;
}

// -----------------------------------------------------------------------------

template<class SerialPort, class Settings>
inline Channel MidiInterface<SerialPort, Settings>::getInputChannel() const
{
    return mInputChannel;
}

/*! \brief Set the value for the input MIDI channel
\param inChannel the channel value. Valid values are 1 to 16, MIDI_CHANNEL_OMNI
if you want to listen to all channels, and MIDI_CHANNEL_OFF to disable input.
*/
template<class SerialPort, class Settings>
inline void MidiInterface<SerialPort, Settings>::setInputChannel(Channel inChannel)
{
    mInputChannel = inChannel;
}

// -----------------------------------------------------------------------------

/*! \brief Extract an enumerated MIDI type from a status byte.

This is a utility static method, used internally,
made public so you can handle MidiTypes more easily.
*/
template<class SerialPort, class Settings>
MidiType MidiInterface<SerialPort, Settings>::getTypeFromStatusByte(byte inStatus)
{
    if ((inStatus  < 0x80) ||
        (inStatus == 0xf4) ||
        (inStatus == 0xf5) ||
        (inStatus == 0xf9) ||
        (inStatus == 0xfD))
    {
        // Data bytes and undefined.
        return InvalidType;
    }
    if (inStatus < 0xf0)
    {
        // Channel message, remove channel nibble.
        return MidiType(inStatus & 0xf0);
    }

    return MidiType(inStatus);
}

/*! \brief Returns channel in the range 1-16
*/
template<class SerialPort, class Settings>
inline Channel MidiInterface<SerialPort, Settings>::getChannelFromStatusByte(byte inStatus)
{
    return (inStatus & 0x0f) + 1;
}

template<class SerialPort, class Settings>
bool MidiInterface<SerialPort, Settings>::isChannelMessage(MidiType inType)
{
    return (inType == NoteOff ||
        inType == NoteOn ||
        inType == ControlChange ||
        inType == AfterTouchPoly ||
        inType == AfterTouchChannel ||
        inType == PitchBend ||
        inType == ProgramChange);
}

// -----------------------------------------------------------------------------

/*! \addtogroup callbacks
@{
*/

template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleNoteOff(void(*fptr)(byte channel, byte note, byte velocity))          { mNoteOffCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleNoteOn(void(*fptr)(byte channel, byte note, byte velocity))           { mNoteOnCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleAfterTouchPoly(void(*fptr)(byte channel, byte note, byte pressure))   { mAfterTouchPolyCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleControlChange(void(*fptr)(byte channel, byte number, byte value))     { mControlChangeCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleProgramChange(void(*fptr)(byte channel, byte number))                 { mProgramChangeCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleAfterTouchChannel(void(*fptr)(byte channel, byte pressure))           { mAfterTouchChannelCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandlePitchBend(void(*fptr)(byte channel, int bend))                        { mPitchBendCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleSystemExclusive(void(*fptr)(byte* array, unsigned size))              { mSystemExclusiveCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleTimeCodeQuarterFrame(void(*fptr)(byte data))                          { mTimeCodeQuarterFrameCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleSongPosition(void(*fptr)(unsigned beats))                             { mSongPositionCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleSongSelect(void(*fptr)(byte songnumber))                              { mSongSelectCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleTuneRequest(void(*fptr)(void))                                        { mTuneRequestCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleClock(void(*fptr)(void))                                              { mClockCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleStart(void(*fptr)(void))                                              { mStartCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleContinue(void(*fptr)(void))                                           { mContinueCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleStop(void(*fptr)(void))                                               { mStopCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleActiveSensing(void(*fptr)(void))                                      { mActiveSensingCallback = fptr; }
template<class SerialPort, class Settings> void MidiInterface<SerialPort, Settings>::setHandleSystemReset(void(*fptr)(void))                                        { mSystemResetCallback = fptr; }

/*! \brief Detach an external function from the given type.

Use this method to cancel the effects of setHandle********.
\param inType        The type of message to unbind.
When a message of this type is received, no function will be called.
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::disconnectCallbackFromType(MidiType inType)
{
    switch (inType)
    {
    case NoteOff:               mNoteOffCallback = 0; break;
    case NoteOn:                mNoteOnCallback = 0; break;
    case AfterTouchPoly:        mAfterTouchPolyCallback = 0; break;
    case ControlChange:         mControlChangeCallback = 0; break;
    case ProgramChange:         mProgramChangeCallback = 0; break;
    case AfterTouchChannel:     mAfterTouchChannelCallback = 0; break;
    case PitchBend:             mPitchBendCallback = 0; break;
    case SystemExclusive:       mSystemExclusiveCallback = 0; break;
    case TimeCodeQuarterFrame:  mTimeCodeQuarterFrameCallback = 0; break;
    case SongPosition:          mSongPositionCallback = 0; break;
    case SongSelect:            mSongSelectCallback = 0; break;
    case TuneRequest:           mTuneRequestCallback = 0; break;
    case Clock:                 mClockCallback = 0; break;
    case Start:                 mStartCallback = 0; break;
    case Continue:              mContinueCallback = 0; break;
    case Stop:                  mStopCallback = 0; break;
    case ActiveSensing:         mActiveSensingCallback = 0; break;
    case SystemReset:           mSystemResetCallback = 0; break;
    default:
        break;
    }
}

/*! @} */ // End of doc group MIDI Callbacks

// Private - launch callback function based on received type.
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::launchCallback()
{
    // The order is mixed to allow frequent messages to trigger their callback faster.
    switch (mMessage.type)
    {
        // Notes
    case NoteOff:               if (mNoteOffCallback != 0)               mNoteOffCallback(mMessage.channel, mMessage.data1, mMessage.data2);   break;
    case NoteOn:                if (mNoteOnCallback != 0)                mNoteOnCallback(mMessage.channel, mMessage.data1, mMessage.data2);    break;

        // Real-time messages
    case Clock:                 if (mClockCallback != 0)                 mClockCallback();           break;
    case Start:                 if (mStartCallback != 0)                 mStartCallback();           break;
    case Continue:              if (mContinueCallback != 0)              mContinueCallback();        break;
    case Stop:                  if (mStopCallback != 0)                  mStopCallback();            break;
    case ActiveSensing:         if (mActiveSensingCallback != 0)         mActiveSensingCallback();   break;

        // Continuous controllers
    case ControlChange:         if (mControlChangeCallback != 0)         mControlChangeCallback(mMessage.channel, mMessage.data1, mMessage.data2);    break;
    case PitchBend:             if (mPitchBendCallback != 0)             mPitchBendCallback(mMessage.channel, (int)((mMessage.data1 & 0x7f) | ((mMessage.data2 & 0x7f) << 7)) + MIDI_PITCHBEND_MIN); break; // TODO: check this
    case AfterTouchPoly:        if (mAfterTouchPolyCallback != 0)        mAfterTouchPolyCallback(mMessage.channel, mMessage.data1, mMessage.data2);    break;
    case AfterTouchChannel:     if (mAfterTouchChannelCallback != 0)     mAfterTouchChannelCallback(mMessage.channel, mMessage.data1);    break;

    case ProgramChange:         if (mProgramChangeCallback != 0)         mProgramChangeCallback(mMessage.channel, mMessage.data1);    break;
    case SystemExclusive:       if (mSystemExclusiveCallback != 0)       mSystemExclusiveCallback(mMessage.sysexArray, mMessage.getSysExSize());    break;

        // Occasional messages
    case TimeCodeQuarterFrame:  if (mTimeCodeQuarterFrameCallback != 0)  mTimeCodeQuarterFrameCallback(mMessage.data1);    break;
    case SongPosition:          if (mSongPositionCallback != 0)          mSongPositionCallback((mMessage.data1 & 0x7f) | ((mMessage.data2 & 0x7f) << 7));    break;
    case SongSelect:            if (mSongSelectCallback != 0)            mSongSelectCallback(mMessage.data1);    break;
    case TuneRequest:           if (mTuneRequestCallback != 0)           mTuneRequestCallback();    break;

    case SystemReset:           if (mSystemResetCallback != 0)           mSystemResetCallback();    break;
    case InvalidType:
    default:
        break;
    }
}

/*! @} */ // End of doc group MIDI Input

// -----------------------------------------------------------------------------
//                                  Thru
// -----------------------------------------------------------------------------

/*! \addtogroup thru
@{
*/

/*! \brief Set the filter for thru mirroring
\param inThruFilterMode a filter mode

@see MidiFilterMode
*/
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::setThruFilterMode(MidiFilterMode inThruFilterMode)
{
    mThruFilterMode = inThruFilterMode;
    if (mThruFilterMode != Off)
        mThruActivated = true;
    else
        mThruActivated = false;
}

template<class SerialPort, class Settings>
MidiFilterMode MidiInterface<SerialPort, Settings>::getFilterMode() const
{
    return mThruFilterMode;
}

template<class SerialPort, class Settings>
bool MidiInterface<SerialPort, Settings>::getThruState() const
{
    return mThruActivated;
}

template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::turnThruOn(MidiFilterMode inThruFilterMode)
{
    mThruActivated = true;
    mThruFilterMode = inThruFilterMode;
}

template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::turnThruOff()
{
    mThruActivated = false;
    mThruFilterMode = Off;
}

/*! @} */ // End of doc group MIDI Thru

// This method is called upon reception of a message
// and takes care of Thru filtering and sending.
// - All system messages (System Exclusive, Common and Real Time) are passed
//   to output unless filter is set to Off.
// - Channel messages are passed to the output whether their channel
//   is matching the input channel and the filter setting
template<class SerialPort, class Settings>
void MidiInterface<SerialPort, Settings>::thruFilter(Channel inChannel)
{
    // If the feature is disabled, don't do anything.
    if (!mThruActivated || (mThruFilterMode == Off))
        return;

    // First, check if the received message is Channel
    if (mMessage.type >= NoteOff && mMessage.type <= PitchBend)
    {
        const bool filter_condition = ((mMessage.channel == mInputChannel) ||
            (mInputChannel == MIDI_CHANNEL_OMNI));

        // Now let's pass it to the output
        switch (mThruFilterMode)
        {
        case Full:
            send(mMessage.type,
                mMessage.data1,
                mMessage.data2,
                mMessage.channel);
            break;

        case SameChannel:
            if (filter_condition)
            {
                send(mMessage.type,
                    mMessage.data1,
                    mMessage.data2,
                    mMessage.channel);
            }
            break;

        case DifferentChannel:
            if (!filter_condition)
            {
                send(mMessage.type,
                    mMessage.data1,
                    mMessage.data2,
                    mMessage.channel);
            }
            break;

        case Off:
            // Do nothing.
            // Technically it's impossible to get there because
            // the case was already tested earlier.
            break;

        default:
            break;
        }
    }
    else
    {
        // Send the message to the output
        switch (mMessage.type)
        {
            // Real Time and 1 byte
        case Clock:
        case Start:
        case Stop:
        case Continue:
        case ActiveSensing:
        case SystemReset:
        case TuneRequest:
            sendRealTime(mMessage.type);
            break;

        case SystemExclusive:
            // Send SysEx (0xf0 and 0xf7 are included in the buffer)
            sendSysEx(getSysExArrayLength(), getSysExArray(), true);
            break;

        case SongSelect:
            sendSongSelect(mMessage.data1);
            break;

        case SongPosition:
            sendSongPosition(mMessage.data1 | ((unsigned)mMessage.data2 << 7));
            break;

        case TimeCodeQuarterFrame:
            sendTimeCodeQuarterFrame(mMessage.data1, mMessage.data2);
            break;
        default:
            break;
        }
    }
}

END_MIDI_NAMESPACE
