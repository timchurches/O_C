// Copyright 2015 Tim Churches
//
// Author: Tim Churches (tim.churches@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Number station.

#ifndef PEAKS_BYTEBEATS_BYTEBEAT_H_
#define PEAKS_BYTEBEATS_BYTEBEAT_H_

// #include "stmlib/stmlib.h"

// #include "peaks/drums/svf.h"

#include <stdint.h>
#include "util/util_macros.h"

#include "extern/stmlib_utils_dsp.h"

#include "peaks_gate_processor.h"

namespace peaks {

class ByteBeat {
 public:
  ByteBeat() { }
  ~ByteBeat() { }
  
  void Init();
  int16_t ProcessSingleSample(uint8_t control);
 
  void Configure(int32_t* parameter, bool stepmode) {
      set_equation(parameter[0]);
      set_speed(parameter[1]);
      set_p0(parameter[2]);
      set_p1(parameter[3]);
      set_p2(parameter[4]);
      set_stepmode(stepmode) ;
  }

   inline void set_equation(int32_t equation) {
    equation_ = equation ;
  }

   inline void set_stepmode(bool stepmode) {
    stepmode_ = stepmode ;
  }

  inline void set_speed(int32_t speed) {
    speed_ = speed;
  }
  
  inline void set_p0(int32_t parameter) {
    p0_ = parameter;
  }

  inline void set_p1(int32_t parameter) {
    p1_ = parameter;
  }

  inline void set_p2(int32_t parameter) {
    p2_ = parameter;
  }

  inline bool FillBuffer() const {
    return true;
  }

  inline uint16_t get_parameter(uint8_t param) {
    return equation_ ;
  }
  
 private:
  uint16_t equation_ ;
  uint16_t speed_;
  uint16_t p0_;
  uint16_t p1_;
  uint16_t p2_;
  uint32_t t_; 
  uint32_t phase_;
  bool stepmode_ ;

  uint8_t equation_index_ ;
  
  DISALLOW_COPY_AND_ASSIGN(ByteBeat);
};

}  // namespace peaks

#endif  // PEAKS_BYTEBEATS_BYTEBEAT_H_
