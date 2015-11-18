
void H1200_topButton() {
  if (h1200_settings.apply_value(
          SETTING_INVERSION, h1200_settings.get_value(SETTING_INVERSION) + 1)) {
    menu_state.value_changed = 1;
    MENU_REDRAW = 1;
  }
}

void H1200_lowerButton() {
  if (h1200_settings.apply_value(
          SETTING_INVERSION, h1200_settings.get_value(SETTING_INVERSION) - 1)) {
    menu_state.value_changed = 1;
    MENU_REDRAW = 1;
  }
}

void H1200_rightButton() {
  if (UI_MODE) {
    menu_state.value_changed =
        h1200_settings.apply_value(menu_state.cursor_pos,
                                   menu_state.cursor_value);
    if (menu_state.value_changed)
      MENU_REDRAW = 1;
  }
}

void H1200_leftButton() {
  menu_state.display_notes = !menu_state.display_notes;
  MENU_REDRAW = 1;
}

void H1200_update_ENC() {
  _ENC = false;
  int value = encoder[LEFT].pos();
  if (value != menu_state.cursor_pos) {
    if (UI_MODE) {
      if (value < 0) value = 0;
      else if (value >= SETTING_LAST) value = SETTING_LAST - 1;
      encoder[LEFT].setPos(value);
      menu_state.cursor_pos = value;
      menu_state.cursor_value = h1200_settings.get_value(menu_state.cursor_pos);
      encoder[RIGHT].setPos(menu_state.cursor_value);
    } else {
      UI_MODE = 1;
    }
    MENU_REDRAW = 1;
    _UI_TIMESTAMP = millis();
  }

  if (UI_MODE) {
    value = encoder[RIGHT].pos();
    if (value != menu_state.cursor_value) {
      menu_state.cursor_value = H1200Settings::clamp_value(menu_state.cursor_pos, value);
      encoder[RIGHT].setPos(menu_state.cursor_value);
      MENU_REDRAW = 1;
      _UI_TIMESTAMP = millis();
    }
  }
}