
/* Copyright (C) 2007 The SpringLobby Team. All rights reserved. */
//
// Class: ChatOptionsTab
//

#include <wx/filedlg.h>
#include <wx/dirdlg.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/intl.h>
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/stdpaths.h>
#include <wx/settings.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/checkbox.h>

#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif

#include "nonportable.h"
#include "chatoptionstab.h"
#include "ui.h"
#include "iunitsync.h"
#include "utils.h"
#include "uiutils.h"
#include "settings.h"
#include "spring.h"
#include "mainwindow.h"
#include "Helper/colorbutton.h"

BEGIN_EVENT_TABLE( ChatOptionsTab, wxPanel )
  EVT_BUTTON( ID_SELFONT, ChatOptionsTab::OnSelectFont )
  EVT_CHECKBOX( ID_SYSCOLS, ChatOptionsTab::OnUseSystemColors )
  EVT_BUTTON( ID_NORMAL, ChatOptionsTab::OnNormalSelect )
  EVT_BUTTON( ID_BG, ChatOptionsTab::OnBGSelect )
  EVT_BUTTON( ID_ACTION, ChatOptionsTab::OnActionSelect )
  EVT_BUTTON( ID_HIGHLIGHT, ChatOptionsTab::OnHighlightSelect )
  EVT_BUTTON( ID_JOINLEAVE, ChatOptionsTab::OnJoinLeaveSelect )
  EVT_BUTTON( ID_NOTIFICATION, ChatOptionsTab::OnNotificationSelect )
  EVT_BUTTON( ID_MYMESS, ChatOptionsTab::OnMyMessSelect )
  EVT_BUTTON( ID_SERVER, ChatOptionsTab::OnServerSelect )
  EVT_BUTTON( ID_CLIENT, ChatOptionsTab::OnClientSelect )
  EVT_BUTTON( ID_ERROR, ChatOptionsTab::OnErrorSelect )
  EVT_BUTTON( ID_TIMESTAMP, ChatOptionsTab::OnTimestampSelect )
  EVT_CHECKBOX( ID_SAVELOGS, ChatOptionsTab::OnSaveLogs )
  EVT_BUTTON( ID_BROWSE_LOGS, ChatOptionsTab::OnBrowseLog )
END_EVENT_TABLE()


ChatOptionsTab::ChatOptionsTab( wxWindow* parent, Ui& ui ) : wxPanel( parent, -1 ),m_ui(ui)
{

  wxBoxSizer* bMainSizerV;
  bMainSizerV = new wxBoxSizer( wxVERTICAL );

  wxStaticBoxSizer* sbColorsSizer;
  sbColorsSizer = new wxStaticBoxSizer( new wxStaticBox( this, -1, _("Colors and font") ), wxHORIZONTAL );

  wxBoxSizer* bColorsVSizer;
  bColorsVSizer = new wxBoxSizer( wxVERTICAL );

  m_use_sys_colors = new wxCheckBox( this, ID_SYSCOLS, _("Use system colors"), wxDefaultPosition, wxDefaultSize, 0 );

  m_use_sys_colors->Enable( false );

  bColorsVSizer->Add( m_use_sys_colors, 0, wxALL, 5 );

  m_custom_colors = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  m_custom_colors->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

  wxBoxSizer* bCustomColorsSizer;
  bCustomColorsSizer = new wxBoxSizer( wxHORIZONTAL );

  wxBoxSizer* bColorSizer;
  bColorSizer = new wxBoxSizer( wxHORIZONTAL );

  wxBoxSizer* bColorsSizer1;
  bColorsSizer1 = new wxBoxSizer( wxVERTICAL );

  wxBoxSizer* bNormlColorSizer;
  bNormlColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_normal_color = new ColorButton( m_custom_colors, ID_NORMAL, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_normal_color->SetColor( wxColour( 0, 0, 0 ) );

  bNormlColorSizer->Add( m_normal_color, 0, wxALL, 5 );

  m_normal_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Normal"), wxDefaultPosition, wxDefaultSize, 0 );
  m_normal_label->Wrap( -1 );
  bNormlColorSizer->Add( m_normal_label, 1, wxALL, 5 );

  bColorsSizer1->Add( bNormlColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bBGColorSizer;
  bBGColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_bg_color = new ColorButton( m_custom_colors, ID_BG, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_bg_color->SetColor( wxColour( 255, 255, 255 ) );

  bBGColorSizer->Add( m_bg_color, 0, wxALL, 5 );

  m_bg_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Background"), wxDefaultPosition, wxDefaultSize, 0 );
  m_bg_label->Wrap( -1 );
  bBGColorSizer->Add( m_bg_label, 1, wxALL, 5 );

  bColorsSizer1->Add( bBGColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bActionColorSizer;
  bActionColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_action_color = new ColorButton( m_custom_colors, ID_ACTION, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_action_color->SetColor( wxColour( 255, 0, 249 ) );

  bActionColorSizer->Add( m_action_color, 0, wxALL, 5 );

  m_action_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Action"), wxDefaultPosition, wxDefaultSize, 0 );
  m_action_label->Wrap( -1 );
  bActionColorSizer->Add( m_action_label, 1, wxALL, 5 );

  bColorsSizer1->Add( bActionColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bHighlightColorSizer;
  bHighlightColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_highlight_color = new ColorButton( m_custom_colors, ID_HIGHLIGHT, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_highlight_color->SetColor( wxColour( 255, 0, 44 ) );

  bHighlightColorSizer->Add( m_highlight_color, 0, wxALL, 5 );

  m_highlight_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Highlight"), wxDefaultPosition, wxDefaultSize, 0 );
  m_highlight_label->Wrap( -1 );
  bHighlightColorSizer->Add( m_highlight_label, 1, wxALL, 5 );

  bColorsSizer1->Add( bHighlightColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bJoinLeaveColorSizer;
  bJoinLeaveColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_joinleave_color = new ColorButton( m_custom_colors, ID_JOINLEAVE, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_joinleave_color->SetColor( wxColour( 24, 255, 0 ) );

  bJoinLeaveColorSizer->Add( m_joinleave_color, 0, wxALL, 5 );

  m_joinleave_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Join/Leave"), wxDefaultPosition, wxDefaultSize, 0 );
  m_joinleave_label->Wrap( -1 );
  bJoinLeaveColorSizer->Add( m_joinleave_label, 1, wxALL, 5 );

  bColorsSizer1->Add( bJoinLeaveColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bMyColorSizer;
  bMyColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_my_color = new ColorButton( m_custom_colors, ID_MYMESS, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_my_color->SetColor( wxColour( 160, 160, 160 ) );

  bMyColorSizer->Add( m_my_color, 0, wxALL, 5 );

  m_my_label = new wxStaticText( m_custom_colors, wxID_ANY, _("My messages"), wxDefaultPosition, wxDefaultSize, 0 );
  m_my_label->Wrap( -1 );
  bMyColorSizer->Add( m_my_label, 1, wxALL, 5 );

  bColorsSizer1->Add( bMyColorSizer, 1, wxEXPAND, 5 );

  bColorSizer->Add( bColorsSizer1, 1, wxEXPAND, 5 );

  wxBoxSizer* bColorSizer2;
  bColorSizer2 = new wxBoxSizer( wxVERTICAL );

  wxBoxSizer* bServerColorSizer;
  bServerColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_server_color = new ColorButton( m_custom_colors, ID_SERVER, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_server_color->SetColor( wxColour( 255, 189, 0 ) );

  bServerColorSizer->Add( m_server_color, 0, wxALL, 5 );

  m_server_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Server"), wxDefaultPosition, wxDefaultSize, 0 );
  m_server_label->Wrap( -1 );
  bServerColorSizer->Add( m_server_label, 1, wxALL, 5 );

  bColorSizer2->Add( bServerColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bClientolorSizer;
  bClientolorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_client_color = new ColorButton( m_custom_colors, ID_CLIENT, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_client_color->SetColor( wxColour( 255, 189, 0 ) );

  bClientolorSizer->Add( m_client_color, 0, wxALL, 5 );

  m_client_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Client"), wxDefaultPosition, wxDefaultSize, 0 );
  m_client_label->Wrap( -1 );
  bClientolorSizer->Add( m_client_label, 1, wxALL, 5 );

  bColorSizer2->Add( bClientolorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bErrorColorSizer;
  bErrorColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_error_color = new ColorButton( m_custom_colors, ID_ERROR, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_error_color->SetColor( wxColour( 255, 0, 0 ) );

  bErrorColorSizer->Add( m_error_color, 0, wxALL, 5 );

  m_error_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Error"), wxDefaultPosition, wxDefaultSize, 0 );
  m_error_label->Wrap( -1 );
  bErrorColorSizer->Add( m_error_label, 1, wxALL, 5 );

  bColorSizer2->Add( bErrorColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bTSColorSizer;
  bTSColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_ts_color = new ColorButton( m_custom_colors, ID_TIMESTAMP, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_ts_color->SetColor( wxColour( 160, 160, 160 ) );

  bTSColorSizer->Add( m_ts_color, 0, wxALL, 5 );

  m_ts_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Timestamp"), wxDefaultPosition, wxDefaultSize, 0 );
  m_ts_label->Wrap( -1 );
  bTSColorSizer->Add( m_ts_label, 1, wxALL, 5 );

  bColorSizer2->Add( bTSColorSizer, 0, wxEXPAND, 5 );

  wxBoxSizer* bNoteColorSizer;
  bNoteColorSizer = new wxBoxSizer( wxHORIZONTAL );

  m_note_color = new ColorButton( m_custom_colors, ID_NOTIFICATION, wxBitmap(), wxDefaultPosition, wxSize( 20,20 ), 0 );
  m_note_color->SetColor( wxColour( 255, 191, 0 ) );

  bNoteColorSizer->Add( m_note_color, 0, wxALL, 5 );

  m_note_label = new wxStaticText( m_custom_colors, wxID_ANY, _("Notification"), wxDefaultPosition, wxDefaultSize, 0 );
  m_note_label->Wrap( -1 );
  bNoteColorSizer->Add( m_note_label, 1, wxALL, 5 );

  bColorSizer2->Add( bNoteColorSizer, 0, wxEXPAND, 5 );

  bColorSizer->Add( bColorSizer2, 1, wxEXPAND, 5 );

  bCustomColorsSizer->Add( bColorSizer, 1, wxEXPAND, 5 );

  m_test_text = new wxTextCtrl( m_custom_colors, wxID_ANY, _("[19:35] ** Server ** Connected to TAS Server.\n[22:30] <Dude> hi everyone\n[22:30] ** Dude2 joined the channel.\n[22:30] * Dude2 thinks his colors looks nice\n[22:45] <Dude> Dude2: orl?\n[22:46] <Dude2> But could be better, should tweak them some more...\n"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH );
  bCustomColorsSizer->Add( m_test_text, 1, wxALL|wxEXPAND, 5 );

  m_custom_colors->SetSizer( bCustomColorsSizer );
  m_custom_colors->Layout();
  bCustomColorsSizer->Fit( m_custom_colors );
  bColorsVSizer->Add( m_custom_colors, 1, wxEXPAND | wxALL, 0 );

  wxBoxSizer* bFontNameSizer;
  bFontNameSizer = new wxBoxSizer( wxHORIZONTAL );

  m_font_label = new wxStaticText( this, wxID_ANY, _("Font:"), wxDefaultPosition, wxDefaultSize, 0 );
  m_font_label->Wrap( -1 );
  bFontNameSizer->Add( m_font_label, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

  m_fontname = new wxStaticText( this, wxID_ANY, _("default"), wxDefaultPosition, wxDefaultSize, 0 );
  m_fontname->Wrap( -1 );
  bFontNameSizer->Add( m_fontname, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

  m_select_font = new wxButton( this, ID_SELFONT, _("Select..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
  bFontNameSizer->Add( m_select_font, 0, wxALL, 5 );

  bColorsVSizer->Add( bFontNameSizer, 0, wxEXPAND, 5 );

  sbColorsSizer->Add( bColorsVSizer, 1, wxEXPAND, 5 );

  bMainSizerV->Add( sbColorsSizer, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );



  wxStaticBoxSizer* sbBehaviorSizer;
  sbBehaviorSizer = new wxStaticBoxSizer( new wxStaticBox( this, -1, _("Behavior") ), wxHORIZONTAL );

  m_smart_scroll = new wxCheckBox( this, ID_SYSCOLS, _("Use smart scrolling"), wxDefaultPosition, wxDefaultSize, 0 );
  m_smart_scroll->SetValue( sett().GetSmartScrollEnabled() );

  sbBehaviorSizer->Add( m_smart_scroll, 0, wxALL, 5 );
#ifndef DISABLE_SOUND
  m_play_sounds = new wxCheckBox( this, ID_PLAY_SOUNDS, _("Play notification sounds"), wxDefaultPosition, wxDefaultSize, 0 );
  m_play_sounds->SetValue( sett().GetChatPMSoundNotificationEnabled() );
  sbBehaviorSizer->Add( m_play_sounds, 0, wxALL, 5 );
#endif


  bMainSizerV->Add( sbBehaviorSizer, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );


  wxBoxSizer* bBotomSizer;
  bBotomSizer = new wxBoxSizer( wxHORIZONTAL );

  wxStaticBoxSizer* sbChatLogSizer;
  wxStaticBox*  sbChatLog = new wxStaticBox( this, -1, _("Chat logs") );
  sbChatLogSizer = new wxStaticBoxSizer( sbChatLog, wxVERTICAL );

  m_save_logs = new wxCheckBox( this, ID_SAVELOGS, _("Save chat logs"), wxDefaultPosition, wxDefaultSize, 0 );
  m_save_logs->SetValue( sett().GetChatLogEnable() );

  sbChatLogSizer->Add( m_save_logs, 0, wxALL, 5 );

  wxBoxSizer* bSaveToSizer;
  bSaveToSizer = new wxBoxSizer( wxHORIZONTAL );

  m_chat_save_label = new wxStaticText( this, wxID_ANY, _("Save to:"), wxDefaultPosition, wxDefaultSize, 0 );
  m_chat_save_label->Wrap( -1 );
  m_chat_save_label->Enable( sett().GetChatLogEnable() );

  bSaveToSizer->Add( m_chat_save_label, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

  m_log_save = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  m_log_save->Enable( sett().GetChatLogEnable() );

  bSaveToSizer->Add( m_log_save, 1, wxALL, 5 );

  m_browse_log = new wxButton( this, ID_BROWSE_LOGS, _("Browse..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
  m_browse_log->Enable( sett().GetChatLogEnable() );

  bSaveToSizer->Add( m_browse_log, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );

  sbChatLogSizer->Add( bSaveToSizer, 0, wxEXPAND, 5 );

  bBotomSizer->Add( sbChatLogSizer, 1, wxEXPAND|wxRIGHT, 5 );

  wxStaticBoxSizer* sbHighlightSizer;
  sbHighlightSizer = new wxStaticBoxSizer( new wxStaticBox( this, -1, _("Highlight words") ), wxVERTICAL );

  m_hilight_words_label = new wxStaticText( this, wxID_ANY, _("Words to highlight in chat:"), wxDefaultPosition, wxDefaultSize, 0 );
  m_hilight_words_label->Wrap( -1 );

  sbHighlightSizer->Add( m_hilight_words_label, 0, wxALL, 5 );


  sbHighlightSizer->Add( 0, 0, 1, wxEXPAND, 5 );

  m_highlight_words = new wxTextCtrl( this, ID_HIWORDS, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  m_highlight_words->SetToolTip ( _("enter a ; seperated list" ) );

  sbHighlightSizer->Add( m_highlight_words, 0, wxALL|wxEXPAND, 5 );

  m_highlight_req = new wxCheckBox( this, ID_HL_REQ, _("Additionally play sound/flash titlebar "), wxDefaultPosition, wxDefaultSize, 0 );
  sbHighlightSizer->Add( m_highlight_req , 0, wxALL|wxEXPAND, 5 );

  bBotomSizer->Add( sbHighlightSizer, 1, wxEXPAND, 5 );

  bMainSizerV->Add( bBotomSizer, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );


  bMainSizerV->Add( 0, 0, 1, wxEXPAND, 5 );

  this->SetSizer( bMainSizerV );
  this->Layout();

  if ( sett().IsPortableMode() ) sbChatLog->Disable();

  DoRestore();
  UpdateTextSample();
}


ChatOptionsTab::~ChatOptionsTab()
{

}


void ChatOptionsTab::UpdateTextSample()
{
  m_test_text->SetFont( m_chat_font );
  m_test_text->SetBackgroundColour( m_bg_color->GetBackgroundColour() );
  m_test_text->Clear();

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[19:35]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_server_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" ** Server ** Connected to TAS Server.\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:30]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_normal_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" <Dude> hi everyone\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:30]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_joinleave_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" ** Dude2 joined the channel.\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:31]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_action_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" * Dude2 thinks his colors looks nice\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:33]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_note_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("<Dude> Dude2: orl?\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:33]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_my_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" <Dude2> Yeah, but could be better, should tweak them some more...\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:33]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_highlight_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" <Dude> bla bla bla Highlighted word bla bla.\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:33]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_error_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" !! Error error.\n") );

  m_test_text->SetDefaultStyle(wxTextAttr( m_ts_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T("[22:33]") );
  m_test_text->SetDefaultStyle(wxTextAttr( m_client_color->GetColor(), m_bg_color->GetBackgroundColour(), m_chat_font ));
  m_test_text->AppendText( _T(" ** Client message.") );

}


void ChatOptionsTab::DoRestore()
{
  m_normal_color->SetColor( sett().GetChatColorNormal() );
  m_bg_color->SetColor( sett().GetChatColorBackground() );
  m_action_color->SetColor( sett().GetChatColorAction() );
  m_highlight_color->SetColor( sett().GetChatColorHighlight() );
  m_joinleave_color->SetColor( sett().GetChatColorJoinPart() );
  m_note_color->SetColor( sett().GetChatColorNotification() );
  m_my_color->SetColor( sett().GetChatColorMine() );
  m_server_color->SetColor( sett().GetChatColorServer() );
  m_client_color->SetColor( sett().GetChatColorClient() );
  m_error_color->SetColor( sett().GetChatColorError() );
  m_ts_color->SetColor( sett().GetChatColorTime() );
  m_chat_font = sett().GetChatFont();
  m_fontname->SetLabel( m_chat_font.GetFaceName() );
  m_save_logs->SetValue(  sett().GetChatLogEnable() );
  m_log_save->SetValue(  sett().GetChatLogLoc() );
  m_smart_scroll->SetValue(sett().GetSmartScrollEnabled());
  m_highlight_words->SetValue( sett().GetHighlightedWords() );
  m_highlight_req->SetValue( sett().GetRequestAttOnHighlight() );
  #ifndef DISABLE_SOUND
    m_play_sounds->SetValue( sett().GetChatPMSoundNotificationEnabled() );
  #endif
}

void ChatOptionsTab::OnApply( wxCommandEvent& event )
{
  sett().SetChatColorNormal ( m_normal_color->GetColor() );
  sett().SetChatColorBackground( m_bg_color->GetColor() );
  sett().SetChatColorAction( m_action_color->GetColor() );
  sett().SetChatColorHighlight( m_highlight_color->GetColor() );
  sett().SetChatColorJoinPart(m_joinleave_color->GetColor() );
  sett().SetChatColorNotification( m_note_color->GetColor() );
  sett().SetChatColorMine( m_my_color->GetColor() );
  sett().SetChatColorServer( m_server_color->GetColor() );
  sett().SetChatColorClient( m_client_color->GetColor() );
  sett().SetChatColorError( m_error_color->GetColor() );
  sett().SetChatColorTime( m_ts_color->GetColor() );
  sett().SetChatFont( m_chat_font );
  //m_ui.mw().GetChatTab().ChangeUnreadChannelColour( m_note_color->GetBackgroundColour() );
  //m_ui.mw().GetChatTab().ChangeUnreadPMColour( m_note_color->GetBackgroundColour() );
  sett().SetHighlightedWords( m_highlight_words->GetValue() );
  sett().SetRequestAttOnHighlight( m_highlight_req->IsChecked() );

  //Chat Log
  sett().SetChatLogEnable( m_save_logs->GetValue());
  sett().SetChatLogLoc( m_log_save->GetValue() );

  // Behavior
  sett().SetSmartScrollEnabled(m_smart_scroll->GetValue());
  #ifndef DISABLE_SOUND
    sett().SetChatPMSoundNotificationEnabled( m_play_sounds->IsChecked() );
  #endif

}


void ChatOptionsTab::OnRestore( wxCommandEvent& event )
{
  DoRestore();
}


void ChatOptionsTab::OnSelectFont( wxCommandEvent& event )
{
  wxFontData data;
  data.SetChosenFont( m_chat_font );
  wxFontDialog dlg( 0, data );
  if ( dlg.ShowModal() == wxID_OK ) {
    m_chat_font = dlg.GetFontData().GetChosenFont();
    m_fontname->SetLabel( m_chat_font.GetFaceName() );
    this->Layout();
    UpdateTextSample();
  }
}


void ChatOptionsTab::OnUseSystemColors( wxCommandEvent& event )
{
}

void ChatOptionsTab::OnColorChange( ColorButton* button )
{
  wxColor c = GetColourFromUser( this, button->GetColor() );
  if ( c.IsOk() ) {
    button->SetColor( c );
  }
  UpdateTextSample();
}

void ChatOptionsTab::OnNormalSelect( wxCommandEvent& event )
{
  OnColorChange( m_normal_color );
}

void ChatOptionsTab::OnBGSelect( wxCommandEvent& event )
{
  OnColorChange( m_bg_color );
}

void ChatOptionsTab::OnActionSelect( wxCommandEvent& event )
{
  OnColorChange( m_action_color );
}

void ChatOptionsTab::OnHighlightSelect( wxCommandEvent& event )
{
  OnColorChange( m_highlight_color );
}

void ChatOptionsTab::OnJoinLeaveSelect( wxCommandEvent& event )
{
  OnColorChange( m_joinleave_color );
}

void ChatOptionsTab::OnNotificationSelect( wxCommandEvent& event )
{
  OnColorChange( m_note_color );
}

void ChatOptionsTab::OnMyMessSelect( wxCommandEvent& event )
{
  OnColorChange( m_my_color );
}

void ChatOptionsTab::OnServerSelect( wxCommandEvent& event )
{
  OnColorChange( m_server_color );
}

void ChatOptionsTab::OnClientSelect( wxCommandEvent& event )
{
  OnColorChange( m_client_color );
}

void ChatOptionsTab::OnErrorSelect( wxCommandEvent& event )
{
  OnColorChange( m_error_color );
}

void ChatOptionsTab::OnTimestampSelect( wxCommandEvent& event )
{
  OnColorChange( m_ts_color );
}

void ChatOptionsTab::OnSaveLogs( wxCommandEvent& event )
{
  m_log_save->Enable( m_save_logs->GetValue() );
  m_browse_log->Enable( m_save_logs->GetValue() );
  m_chat_save_label->Enable( m_save_logs->GetValue() );
}

void ChatOptionsTab::OnBrowseLog( wxCommandEvent& event )
{
  wxDirDialog dirpic( this, _("Choose a directory"), sett().GetSpringDir(), wxDD_DEFAULT_STYLE );
  if ( dirpic.ShowModal() == wxID_OK ) m_log_save->SetValue( dirpic.GetPath() );
}

