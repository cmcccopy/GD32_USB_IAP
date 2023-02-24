/*!
    \file  readme.txt
    \brief description of the USB MSC device for IAP demo

    \version 2018-06-01, V1.0.0, firmware for GD32 USBFS
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

  The target of this example apply for GD32F107xx family(F107C EVAL board),GD32F207xx 
family(F207I EVAL board),GD32F307xx family(F307C EVAL board),GD32F403xx family(F403Z EVAL 
board),GD32F450xx family(F450I EVAL board),GD32F350xx family(F350R EVAL board) and GD32E103xx 
family(E103V EVAL board).

  This demo provides a description of how to use the USBFS peripheral. The GD32
device is enumerated as an USB MSC device for IAP, that uses the native PC host MSC driver.

  To test the demo, you need a configuration bin image. The bin image should set application 
address at 0x08020000(F107C, F207I, F307C, F403Z and F450I), 0x08010000(E103V) or 0x08013800(F350R).
You can refer to "../Test_Images" folder and use the bin images in it, .

  To test the demo, you need to:
    - Connect GD32 USB to PC, and identifies a new removable storage device
    - Copy the "update.bin" image to the new U-disk
    - After each device reset, the mcu will run the new application
    - After each device reset, hold down the USER key on the board to enter IAP mode

  Note:
       1.The F350R EVAL board needs to manually format the U-disk.
       2.The file name of the bin that was copied into the U-disk needs to be changed to update.bin.
