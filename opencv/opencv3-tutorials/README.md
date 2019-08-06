OpenCV Samples
==============

[compile opencv]
1. download opencv-3.4.6
2. download opencv_contrib-3.4.6
3. cd opencv-3.4.6 && mkdir build && cd build
4. export CXX_FLAGS='-std=c++11 -Wno-narrowing'
5. cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-3.4.6/modules/ \
         -DBUILD_EXAMPLES=ON \
         -DOPENCV_ENABLE_NONFREE=ON \
         ..
6. make -j4 && sudo make install
