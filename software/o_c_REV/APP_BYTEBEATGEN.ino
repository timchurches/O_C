
#include "OC_apps.h"
#include "OC_bitmaps.h"
#include "OC_digital_inputs.h"
#include "OC_strings.h"
#include "util/util_math.h"
#include "util/util_settings.h"
#include "OC_menus.h"
#include "peaks_bytebeat.h"

enum ByteBeatSettings {
  BYTEBEAT_SETTING_EQUATION,
  BYTEBEAT_SETTING_SPEED,
  BYTEBEAT_SETTING_P0,
  BYTEBEAT_SETTING_P1,
  BYTEBEAT_SETTING_P2,
  BYTEBEAT_SETTING_TRIGGER_INPUT,
  BYTEBEAT_SETTING_CV1,
  BYTEBEAT_SETTING_CV2,
  BYTEBEAT_SETTING_CV3,
  BYTEBEAT_SETTING_CV4,
  BYTEBEAT_SETTING_LAST,
  BYTEBEAT_SETTING_FIRST=BYTEBEAT_SETTING_EQUATION,
};

enum ByteBeatCVMapping {
  BYTEBEAT_CV_MAPPING_NONE,
  BYTEBEAT_CV_MAPPING_EQUATION,
  BYTEBEAT_CV_MAPPING_SPEED,
  BYTEBEAT_CV_MAPPING_P0,
  BYTEBEAT_CV_MAPPING_P1,
  BYTEBEAT_CV_MAPPING_P2,
  BYTEBEAT_CV_MAPPING_LAST,
  BYTEBEAT_CV_MAPPING_FIRST=BYTEBEAT_CV_MAPPING_EQUATION
  
};

class ByteBeat : public settings::SettingsBase<ByteBeat, BYTEBEAT_SETTING_LAST> {
public:

  static constexpr int kMaxByteBeatParameters = 5;

  void Init(OC::DigitalInput default_trigger);

  OC::DigitalInput get_trigger_input() const {
    return static_cast<OC::DigitalInput>(values_[BYTEBEAT_SETTING_TRIGGER_INPUT]);
  }

  ByteBeatCVMapping get_cv1_mapping() const {
    return static_cast<ByteBeatCVMapping>(values_[BYTEBEAT_SETTING_CV1]);
  }

  ByteBeatCVMapping get_cv2_mapping() const {
    return static_cast<ByteBeatCVMapping>(values_[BYTEBEAT_SETTING_CV2]);
  }

  ByteBeatCVMapping get_cv3_mapping() const {
    return static_cast<ByteBeatCVMapping>(values_[BYTEBEAT_SETTING_CV3]);
  }

  ByteBeatCVMapping get_cv4_mapping() const {
    return static_cast<ByteBeatCVMapping>(values_[BYTEBEAT_SETTING_CV4]);
  }

  uint8_t get_equation() const {
    return values_[BYTEBEAT_SETTING_EQUATION];
  }

  uint8_t get_speed() const {
    return values_[BYTEBEAT_SETTING_SPEED];
  }

  uint8_t get_p0() const {
    return values_[BYTEBEAT_SETTING_P0];
  }

  uint8_t get_p1() const {
    return values_[BYTEBEAT_SETTING_P1];
  }

  uint8_t get_p2() const {
    return values_[BYTEBEAT_SETTING_P2];
  }

  int32_t get_s(uint8_t param) {
    return s_[param] ; 
  }

  inline void apply_cv_mapping(ByteBeatSettings cv_setting, const int32_t cvs[ADC_CHANNEL_LAST], int32_t segments[kMaxByteBeatParameters]) {
    int mapping = values_[cv_setting];
    uint8_t bytebeat_cv_rshift = 12 ;
    switch (mapping) {
      case BYTEBEAT_CV_MAPPING_EQUATION:
      case BYTEBEAT_CV_MAPPING_SPEED:
      case BYTEBEAT_CV_MAPPING_P0:
      case BYTEBEAT_CV_MAPPING_P1:
      case BYTEBEAT_CV_MAPPING_P2:
        bytebeat_cv_rshift = 12 ;
        break;
      default:
        break;
    }
    segments[mapping - BYTEBEAT_CV_MAPPING_FIRST] += (cvs[cv_setting - BYTEBEAT_SETTING_CV1] * 65536) >> bytebeat_cv_rshift ;
  }

  template <DAC_CHANNEL dac_channel>
  void Update(uint32_t triggers, const int32_t cvs[ADC_CHANNEL_LAST]) {

    int32_t s[kMaxByteBeatParameters];
    s[0] = SCALE8_16(static_cast<int32_t>(get_equation() << 5));
    s[1] = SCALE8_16(static_cast<int32_t>(get_speed()));
    s[2] = SCALE8_16(static_cast<int32_t>(get_p0()));
    s[3] = SCALE8_16(static_cast<int32_t>(get_p1()));
    s[4] = SCALE8_16(static_cast<int32_t>(get_p2()));

    apply_cv_mapping(BYTEBEAT_SETTING_CV1, cvs, s);
    apply_cv_mapping(BYTEBEAT_SETTING_CV2, cvs, s);
    apply_cv_mapping(BYTEBEAT_SETTING_CV3, cvs, s);
    apply_cv_mapping(BYTEBEAT_SETTING_CV4, cvs, s);

    s[0] = USAT16(s[0]);
    s[1] = USAT16(s[1]);
    s[2] = USAT16(s[2]);
    s[3] = USAT16(s[3]);
    s[4] = USAT16(s[4]);

    s_[0] = s[0] ;
    s_[1] = s[1] ;
    s_[2] = s[2] ;
    s_[3] = s[3] ;
    s_[4] = s[4] ;
        
    bytebeat_.Configure(s) ; 

    OC::DigitalInput trigger_input = get_trigger_input();
    uint8_t gate_state = 0;
    if (triggers & DIGITAL_INPUT_MASK(trigger_input))
      gate_state |= peaks::CONTROL_GATE_RISING;

    bool gate_raised = OC::DigitalInputs::read_immediate(trigger_input);
    if (gate_raised)
      gate_state |= peaks::CONTROL_GATE;
    else if (gate_raised_)
      gate_state |= peaks::CONTROL_GATE_FALLING;
    gate_raised_ = gate_raised;

    // TODO Scale range or offset?
    uint32_t value = OC::calibration_data.dac.octaves[_ZERO] + bytebeat_.ProcessSingleSample(gate_state);
    DAC::set<dac_channel>(value);
  }


private:
  peaks::ByteBeat bytebeat_;
  bool gate_raised_;
  int32_t s_[kMaxByteBeatParameters];
};

void ByteBeat::Init(OC::DigitalInput default_trigger) {
  InitDefaults();
  apply_value(BYTEBEAT_SETTING_TRIGGER_INPUT, default_trigger);
  bytebeat_.Init();
  gate_raised_ = false;
}

const char* const bytebeat_cv_mapping_names[BYTEBEAT_CV_MAPPING_LAST] = {
  "off", "equ", "spd", "p0", "p1", "p2" 
};

SETTINGS_DECLARE(ByteBeat, BYTEBEAT_SETTING_LAST) {
  { 0, 0, 7, "Equation", NULL, settings::STORAGE_TYPE_U8 },
  { 128, 0, 255, "Speed", NULL, settings::STORAGE_TYPE_U8 },
  { 128, 0, 255, "Parameter 0", NULL, settings::STORAGE_TYPE_U8 }, 
  { 128, 0, 255, "Parameter 1", NULL, settings::STORAGE_TYPE_U8 }, 
  { 128, 0, 255, "Parameter 2", NULL, settings::STORAGE_TYPE_U8 }, 
  { OC::DIGITAL_INPUT_1, OC::DIGITAL_INPUT_1, OC::DIGITAL_INPUT_4, "Trigger input", OC::Strings::trigger_input_names, settings::STORAGE_TYPE_U4 },
  { BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_LAST - 1, "CV1 -> ", bytebeat_cv_mapping_names, settings::STORAGE_TYPE_U4 },
  { BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_LAST - 1, "CV2 -> ", bytebeat_cv_mapping_names, settings::STORAGE_TYPE_U4 },
  { BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_LAST - 1, "CV3 -> ", bytebeat_cv_mapping_names, settings::STORAGE_TYPE_U4 },
  { BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_NONE, BYTEBEAT_CV_MAPPING_LAST - 1, "CV4 -> ", bytebeat_cv_mapping_names, settings::STORAGE_TYPE_U4 },
};

class QuadByteBeats {
public:
  static constexpr int32_t kCvSmoothing = 16;

  // bb = bytebeat, balls_ = bytebeats_, BouncingBall = Bytebeat
  // QuadBouncingBalls = QuadByteBeats, bbgen = bytebeatgen, BBGEN = BYTEBEATGEN

  void Init() {
    int input = OC::DIGITAL_INPUT_1;
    for (auto &bytebeat : bytebeats_) {
      bytebeat.Init(static_cast<OC::DigitalInput>(input));
      ++input;
    }

    ui.left_encoder_value = 0;
    ui.left_edit_mode = MODE_EDIT_SETTINGS;
    ui.editing = false;
    ui.selected_channel = 0;
    ui.selected_segment = 0;
    ui.selected_setting = BYTEBEAT_SETTING_EQUATION;
  }

  void ISR() {
    cv1.push(OC::ADC::value<ADC_CHANNEL_1>());
    cv2.push(OC::ADC::value<ADC_CHANNEL_2>());
    cv3.push(OC::ADC::value<ADC_CHANNEL_3>());
    cv4.push(OC::ADC::value<ADC_CHANNEL_4>());

    const int32_t cvs[ADC_CHANNEL_LAST] = { cv1.value(), cv2.value(), cv3.value(), cv4.value() };
    uint32_t triggers = OC::DigitalInputs::clocked();

    bytebeats_[0].Update<DAC_CHANNEL_A>(triggers, cvs);
    bytebeats_[1].Update<DAC_CHANNEL_B>(triggers, cvs);
    bytebeats_[2].Update<DAC_CHANNEL_C>(triggers, cvs);
    bytebeats_[3].Update<DAC_CHANNEL_D>(triggers, cvs);
  }

  enum LeftEditMode {
    MODE_SELECT_CHANNEL,
    MODE_EDIT_SETTINGS
  };

  struct {
    LeftEditMode left_edit_mode;
    int left_encoder_value;
    bool editing;

    int selected_channel;
    int selected_segment;
    int selected_setting;
  } ui;

  ByteBeat &selected() {
    return bytebeats_[ui.selected_channel];
  }

  ByteBeat bytebeats_[4];

  SmoothedValue<int32_t, kCvSmoothing> cv1;
  SmoothedValue<int32_t, kCvSmoothing> cv2;
  SmoothedValue<int32_t, kCvSmoothing> cv3;
  SmoothedValue<int32_t, kCvSmoothing> cv4;
};

QuadByteBeats bytebeatgen;

void BYTEBEATGEN_init() {
  bytebeatgen.Init();
}

size_t BYTEBEATGEN_storageSize() {
  return 4 * ByteBeat::storageSize();
}

size_t BYTEBEATGEN_save(void *storage) {
  size_t s = 0;
  for (auto &bytebeat : bytebeatgen.bytebeats_)
    s += bytebeat.Save(static_cast<byte *>(storage) + s);
  return s;
}

size_t BYTEBEATGEN_restore(const void *storage) {
  size_t s = 0;
  for (auto &bytebeat : bytebeatgen.bytebeats_)
    s += bytebeat.Restore(static_cast<const byte *>(storage) + s);
  return s;
}

void BYTEBEATGEN_handleEvent(OC::AppEvent event) {
  switch (event) {
    case OC::APP_EVENT_RESUME:
      encoder[LEFT].setPos(0);
      encoder[RIGHT].setPos(0);
      break;
    case OC::APP_EVENT_SUSPEND:
    case OC::APP_EVENT_SCREENSAVER:
      break;
  }
}

void BYTEBEATGEN_loop() {
  if (_ENC && (millis() - _BUTTONS_TIMESTAMP > DEBOUNCE)) encoders();
  buttons(BUTTON_TOP);
  buttons(BUTTON_BOTTOM);
  buttons(BUTTON_LEFT);
  buttons(BUTTON_RIGHT);
}

void BYTEBEATGEN_menu_settings() {
  auto const &bytebeat = bytebeatgen.selected();
  UI_START_MENU(0);

  int first_visible_param = bytebeatgen.ui.selected_setting - 3;
  if (first_visible_param < BYTEBEAT_SETTING_EQUATION)
    first_visible_param = BYTEBEAT_SETTING_EQUATION;

  UI_BEGIN_ITEMS_LOOP(kStartX, first_visible_param, BYTEBEAT_SETTING_LAST, bytebeatgen.ui.selected_setting, 0); // was 1
    UI_DRAW_EDITABLE(bytebeatgen.ui.editing);
    UI_DRAW_SETTING(ByteBeat::value_attr(current_item), bytebeat.get_value(current_item), kUiWideMenuCol1X);
  UI_END_ITEMS_LOOP();
}

void BYTEBEATGEN_menu() {
  GRAPHICS_BEGIN_FRAME(false); // no frame, no problem
  static const weegfx::coord_t kStartX = 0;
  UI_DRAW_TITLE(kStartX);

  for (int i = 0, x = 0; i < 4; ++i, x += 32) {
    graphics.setPrintPos(x + 6, 2);
    graphics.print((char)('A' + i));
    graphics.setPrintPos(x + 14, 2);
    if (i == bytebeatgen.ui.selected_channel) {
      graphics.invertRect(x, 0, 32, 11);
    }
  }

  BYTEBEATGEN_menu_settings();

  // TODO Draw phase anyway?
  GRAPHICS_END_FRAME();
}

void BYTEBEATGEN_topButton() {
  auto &selected_bytebeat = bytebeatgen.selected();
  selected_bytebeat.change_value(BYTEBEAT_SETTING_EQUATION + bytebeatgen.ui.selected_setting, 1);
}

void BYTEBEATGEN_lowerButton() {
  auto &selected_bytebeat = bytebeatgen.selected();
  selected_bytebeat.change_value(BYTEBEAT_SETTING_EQUATION + bytebeatgen.ui.selected_setting, -1); 
}

void BYTEBEATGEN_rightButton() {
    bytebeatgen.ui.editing = !bytebeatgen.ui.editing;
    encoder[LEFT].setPos(0);
    encoder[RIGHT].setPos(0);
}

void BYTEBEATGEN_leftButton() {
//  if (QuadByteBeats::MODE_EDIT_SETTINGS == bytebeatbgen.ui.left_edit_mode) {
//    bytebeatgen.ui.left_edit_mode = QuadByteBeats::MODE_SELECT_CHANNEL;
//  } else {
//    bytebeatgen.ui.left_edit_mode = QuadByteBeats::MODE_EDIT_SETTINGS;
//  }
  encoder[LEFT].setPos(0);
  encoder[RIGHT].setPos(0);  
}

void BYTEBEATGEN_leftButtonLong() { }

bool BYTEBEATGEN_encoders() {
  long left_value = encoder[LEFT].pos();
  long right_value = encoder[RIGHT].pos();
  bool changed = left_value || right_value;

  if (QuadByteBeats::MODE_SELECT_CHANNEL == bytebeatgen.ui.left_edit_mode) {
    if (left_value) {
      left_value += bytebeatgen.ui.selected_channel;
      CONSTRAIN(left_value, 0, 3);
      bytebeatgen.ui.selected_channel = left_value;
    }
    if (right_value) {
      auto &selected_bytebeat = bytebeatgen.selected();
      selected_bytebeat.change_value(BYTEBEAT_SETTING_SPEED + bytebeatgen.ui.selected_segment, right_value);
    }
  } else {
    if (left_value) {
      left_value += bytebeatgen.ui.selected_channel;
      CONSTRAIN(left_value, 0, 3);
      bytebeatgen.ui.selected_channel = left_value;
    }
    if (right_value) {
      if (bytebeatgen.ui.editing) {
        auto &selected_bytebeat = bytebeatgen.selected();
        selected_bytebeat.change_value(bytebeatgen.ui.selected_setting, right_value);
      } else {
        right_value += bytebeatgen.ui.selected_setting;
        CONSTRAIN(right_value, BYTEBEAT_SETTING_EQUATION, BYTEBEAT_SETTING_LAST - 1);
        bytebeatgen.ui.selected_setting = right_value;
      }
    }
  }

  encoder[LEFT].setPos(0);
  encoder[RIGHT].setPos(0);
  return changed;
}

void BYTEBEATGEN_debug() {
  graphics.setPrintPos(2, 12);
  graphics.print(bytebeatgen.bytebeats_[0].get_equation());
  graphics.setPrintPos(66, 12);
  graphics.print(bytebeatgen.bytebeats_[0].get_s(0));

  graphics.setPrintPos(2, 22);
  graphics.print(bytebeatgen.bytebeats_[0].get_speed());
  graphics.setPrintPos(66, 22);
  graphics.print(bytebeatgen.bytebeats_[0].get_s(1));
  
  graphics.setPrintPos(2, 32);
  graphics.print(bytebeatgen.bytebeats_[0].get_p0());
  graphics.setPrintPos(66, 32);
  graphics.print(bytebeatgen.bytebeats_[0].get_s(2));

  graphics.setPrintPos(2, 42);
  graphics.print(bytebeatgen.bytebeats_[0].get_p1());
  graphics.setPrintPos(66, 42);
  graphics.print(bytebeatgen.bytebeats_[0].get_s(3));
}

void BYTEBEATGEN_screensaver() {
   GRAPHICS_BEGIN_FRAME(false);
   scope_render();
   GRAPHICS_END_FRAME();
}

void FASTRUN BYTEBEATGEN_isr() {
  bytebeatgen.ISR();
}


