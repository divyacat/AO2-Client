#ifndef COURTROOM_H
#define COURTROOM_H

#include "aoimage.h"
#include "aobutton.h"
#include "aoscene.h"
#include "aomovie.h"
#include "aocharmovie.h"
#include "aomusicplayer.h"
#include "aosfxplayer.h"
#include "aoblipplayer.h"
#include "aolineedit.h"
#include "aotextedit.h"
#include "datatypes.h"
#include "aoapplication.h"
#include "lobby.h"
#include "file_functions.h"
#include "datatypes.h"
#include "debug_functions.h"
#include "aoiclog.h"
#include "aojukebox.h"
#include "aorooms.h"
#include "aomixer.h"
#include "aochat.h"
#include "aoroomcontrols.h"
#include "aoevidence.h"

#include "network/client.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QVector>
#include <QCloseEvent>
#include <QSignalMapper>
#include <QMap>
#include <QTextBrowser>
#include <QSpinBox>

#include <QDebug>
#include <QScrollBar>
#include <QRegExp>
#include <QBrush>
#include <QTextCharFormat>
#include <QFont>
#include <QInputDialog>
#include <QFileDialog>
#include <QAction>

using namespace AttorneyOnline;

class AOApplication;
class AOViewport;

// This is for inline message-colouring.
enum INLINE_COLOURS {
    INLINE_BLUE,
    INLINE_GREEN,
    INLINE_ORANGE,
    INLINE_GREY
};

class Courtroom : public QMainWindow
{
  Q_OBJECT
public:
  explicit Courtroom(AOApplication *p_ao_app);

  void arup_append(int players, QString status, QString cm, QString locked);
  void arup_modify(int type, int place, QString value);

  //called when a DONE#% from the server was received
  void done_received();

  //properly sets up some varibles: resets user state
  void enter_courtroom(int p_cid);

  //these are for OOC chat
  void append_ms_chatmessage(QString f_name, QString f_message);
  void append_server_chatmessage(QString p_name, QString p_message, QString p_colour);

  void handle_chatmessage(QStringList *p_contents);

  void announce_case(QString title, bool def, bool pro, bool jud, bool jur, bool steno);

  void check_connection_received();

  ~Courtroom();

  static constexpr int chatmessage_size = 23;
private:
  AOApplication *ao_app;

  Client *client;

  QString previous_ic_message = "";

  //char id, muted or not
  QMap<int, bool> mute_map;

  int objection_state = 0;
  int realization_state = 0;
  int text_color = 0;
  bool is_presenting_evidence = false;

  int defense_bar_state = 0;
  int prosecution_bar_state = 0;

  AOMusicPlayer *music_player;
  AOSfxPlayer *modcall_player;

  AOViewport *ui_viewport;
  AOICLog *ui_ic_chatlog;
  AORoomChooser *ui_area_list;
  AOJukebox *ui_music_list;
  AOMixer *ui_mixer;
  AOChat *ui_ic_chat;
  AORoomControls *ui_room_controls;
  AOEvidence *ui_evidence;

  AOServerChat *ui_ms_chat;
  AOServerChat *ui_server_chat;

  QAction *ui_change_character;
  QAction *ui_reload_theme;
  QAction *ui_call_mod;
  QAction *ui_settings;
  QAction *ui_announce_case;

  QAction *ui_modcall_notify;
  QAction *ui_casing;
  QAction *ui_showname_enable;

  bool chooseCharacter();

private slots:
  void on_ic_chat_messageSent();
  void on_client_icReceived(const chat_message_type &message);
  void on_client_kicked(const QString &message, bool banned);
  void on_client_trackChanged(const QString &track, const QString &showname);
  void on_client_modCalled(const QString &message);
  void on_client_caseCalled(const QString &message,
                            const std::bitset<CASING_FLAGS_COUNT> casingFlags);

  void on_ooc_return_pressed(QString name, QString message);
  void on_ms_return_pressed(QString name, QString message);
  void on_icChat_positionChanged(QString pos);
  void on_jukebox_trackSelected(QString track);
  void on_rooms_roomSelected(QString room);

  void on_mute_triggered();
  void on_pair_triggered();

  void on_text_color_changed(int p_color);

  void on_music_slider_moved(int p_value);
  void on_sfx_slider_moved(int p_value);
  void on_blip_slider_moved(int p_value);

  void on_roomControls_wtce(WTCE_TYPE type);

  void on_change_character_triggered();
  void on_reload_theme_triggered();
  void on_call_mod_triggered();
  void on_settings_triggered();
  void on_announce_case_triggered();

  void on_showname_enable_triggered();

  void on_quit_triggered();

  void on_casing_triggered();

  void load_bass_opus_plugin();
};

#endif // COURTROOM_H