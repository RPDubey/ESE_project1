/*******************************************************************************
@file:platform.h
@brief:Helps switch platform

This file Helps create an independent layer allowing to switch between platform
specific lower layer functions. For eg. printf function needs to be disabled for
KL25z platform but enabled for BBB and Host.Switch Happens using a compile time
Switch.
@author:Ravi Dubey
@date:09/30/2017
*******************************************************************************/


#ifndef FILE_PLATFORM
#define FILE_PLATFORM

#define ENABLE_LOWLEVEL_FUNCTION

#ifdef KL254Z
#undef ENABLE_LOWLEVEL_FUNCTION
#endif

#endif
