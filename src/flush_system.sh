#!/bin/bash

cd /media/dengtao/win_software/win_software/android5.1_rk3288 && bash /media/dengtao/win_software/win_software/android5.1_rk3288/mkimage.sh
sudo upgrade_tool di -b /media/dengtao/win_software/win_software/android5.1_rk3288/rockdev/Image-rk3288_box/boot.img
sudo upgrade_tool di -s /media/dengtao/win_software/win_software/android5.1_rk3288/rockdev/Image-rk3288_box/system.img