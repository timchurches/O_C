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
 
  void Configure(int32_t* parameter, bool stepmode, bool loopmode) {
      set_equation(parameter[0]);
      set_speed(parameter[1]);
      set_p0(parameter[2]);
      set_p1(parameter[3]);
      set_p2(parameter[4]);
      set_loop_start(parameter[5], parameter[6]);
      set_loop_end(parameter[7], parameter[8]);
      set_step_mode(stepmode) ;
      set_loop_mode(loopmode) ;
      bytepitch_ = (65535 - speed_) >> 8 ; 
      if (bytepitch_ < 1) {
        bytepitch_ = 1;
      }
      equation_index_ = equation_ >> 14 ;
  }

   inline void set_equation(int32_t equation) {
    equation_ = equation ;
  }

   inline void set_step_mode(bool stepmode) {
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

  inline void set_loop_mode(bool loopmode) {
    loopmode_ = loopmode ;
  }

  inline void set_loop_start(int32_t start, int32_t start_fine) {
    // loop_start_ = static_cast<uint32_t>(parameter << 16) ;
    // loop_start_ = 15000;
    loop_start_ = static_cast<uint32_t>((start << 8) + start_fine) ;
  }

  inline void set_loop_end(int32_t end, int32_t end_fine) {
    // loop_end_ = static_cast<uint32_t>(parameter << 16) ;
    // loop_end_ = 54000;
    loop_end_ = static_cast<uint32_t>((end << 8) + end_fine) ;
  }

  inline bool FillBuffer() const {
    return true;
  }

  inline uint32_t get_t() {
    return t_ ;
  }
  
  inline uint32_t get_phase() {
    return phase_ ;
  }

  inline uint32_t get_loop_start() {
    return loop_start_ ;
  }

  inline uint32_t get_loop_end() {
    return loop_end_ ;
  }

  inline uint16_t get_bytepitch() {
    return bytepitch_ ;
  }
  
 private:
  uint16_t equation_ ;
  uint16_t speed_;
  uint16_t p0_;
  uint16_t p1_;
  uint16_t p2_;
  uint32_t t_; 
  uint32_t phase_;
  uint32_t loop_start_ ;
  uint32_t loop_end_ ;
  bool stepmode_ ;
  bool loopmode_ ;

  uint8_t equation_index_ ;
  uint16_t bytepitch_ ;
  
  DISALLOW_COPY_AND_ASSIGN(ByteBeat);
};

}  // namespace peaks

#endif  // PEAKS_BYTEBEATS_BYTEBEAT_H_
