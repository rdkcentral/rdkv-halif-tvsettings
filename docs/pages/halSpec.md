@mainpage

# Control Settings HAL Documentation




# Version and Version History


1.0.0 Initial Revision covers existing Control Settings HAL implementation.


# Description

Controlsettings-hal a.k.a TV settings HAL is an abstract layer, which will provide API to Modify/Control the Picture quality parameters.

![Control Settings HAL diagram](tv_settings_hal_architecture.png)

Control Settings HAL will provide the API's to initialize Video Drivers of PQ server and communicates to the PQ video drivers for controlling the TV settings. 

# Component Runtime Execution Requirements

SOC is responsible for handling the PQ settings at the end device as per the request.
RDK Middleware has to monitor the response continuosly from the drivers upon requesting a settings change in TV.
Failure to meet these requirements will likely result in undefined and unexpected behavior.

## Initialization and Startup

TvSettings HAL API will be initialized by Tv Mgr-Plugin module. RDK-V middleware expected to have complete control over the life cycle over the Control Settings HAL module.
 TV Mgr plugin will first initialize by setting all the PQ parameters 
 1. Initialize the TV Settings hal using the function: tvInit (int *) before configuring any parameters using get/set functions. 
 2. The control settings hal will set all the PQ parameters for different content format and picture modes from the config file(allmodes.conf) as part of initialization.
 3. We can then configure the PQ parameters such as Brightness, Contrast, Hue, ColorTemp, RGB Gain values etc., for different PQ modes using the get/set functions.
 4. We can also reset the parameters to the default value(set by config file) using the reset functions.
 5. Once the required PQ params are configured, we can terminate the tv hal instace using tvTerm().

Need to call the function sequence in above order so that the system behaves
in a deterministic manner, every time.

## Threading Model

Control Settings HAL is not thread safe, any module which is invoking the Control Settings HAL api 
should ensure calls are made in a thread safe manner.
Different SOC vendors allowed to create internal threads to meet the requirements of underlaying 
CEC driver module and meet the operational requirements. SOC should be responsible to synchronize between the calls, events and cleanup the thread.

## Process Model

TVMgr-plugin will take care of Initializing Control Settings HAL component. At any point of time a single instance of TVMgr will exist to 
respond to any requests to configure the PQ parameters from application.

## Memory Model

The Control settings HAL is handling the pointers in heap memory for each of the parameters to be set/get. 
For asynchronous updates, HAL will pass message buffer in the callback and client is responsible to copy to its internal buffer before callback is returned.

## Power Management Requirements

Control Settings HAL does participate in power management., It will cooperate with the PQ Video Drivers for adjusting the PQ settings according to the power mode set.

## Asynchronous Notification Model

Change in Data update can be done asynchronously with the following API’s.
  1. For Updating Video Format change, use this function: RegisterVideoFormatChangeCB(tvVideoFormatCallbackData& cbData)

  2. For updating the Video Resolution change, use this function : RegisterVideoResolutionChangeCB(tvVideoResolutionCallbackData& cbData)

  3.  For updating the video Frame Rate, use this function: RegisterVideoFrameRateChangeCB(tvVideoFrameRateCallbackData& cbData)


## Blocking calls

There are no blocking calls in control settings hal

## Internal Error Handling

All the Control Settings API should return error synchronously as a return argument from any of the types (tvERROR_NONE, tvERROR_GENERAL,tvERROR_OPERATION_NOT_SUPPORTED, tvERROR_INVALID_PARAM, tvERROR_INVALID_STATE or Error codes). HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

TV Settings HAL will initialize the HAL with the parameters present in GENERIC_MODE_CONFIG_FILE(allmodes.conf) .

# Nonfunctional requirements

Following non functional requirement should be supported by the Control Settings HAL component.

## Logging and debugging requirements

Control Settings HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

## Memory and performance requirements

Make sure Control Settings HAL is not contributing more to memory and CPU utilization while handling different power modes.

## Quality Control

There should not be any memory leaks/corruption introduced by HAL and underneath SOC software.

## Licensing

Control Settings HAL implementation is expected to released under the Apache License. 

## Build Requirements

Control Settings HAL source code should be build under Linux Yocto environment and should be delivered as a shared library.
  

## Variability Management

Any new API introduced should be implemented by all SOC vendor and RDK generic code will be compatible with specific version of Control Settings HAL software.

## Platform or Product Customization
Product or platform specific requirements can be handled in Control settings  HAL API and the Specifications for respective product can be modified in config file.

# Interface API Documentation

Covered as per Doxygen documentations.

## Theory of operation and key concepts

Covered as per "Description" sections.

### UML Diagrams

#### Sequence Diagram

![Control Settings HAL Sequence  diagram](sequence_diagram.png)

#### State Diagram

![ControlSettings HAL State Diagram](state_diagram.png)
