//
// Class: IconImageList
//

#ifndef _ICONIMAGELIST_H_
#define _ICONIMAGELIST_H_

#include <wx/imaglist.h>

#define ICON_ADMIN 0
#define ICON_ADMIN_AWAY 1
#define ICON_ADMIN_INGAME 2
#define ICON_BOT 3
#define ICON_NOSTATE -1
#define ICON_AWAY 4
#define ICON_INGAME 5

#define ICON_UP 6
#define ICON_DOWN 7

#define ICON_RANK_NONE -1
#define ICON_RANK0 8
#define ICON_RANK1 9
#define ICON_RANK2 10
#define ICON_RANK3 11
#define ICON_RANK4 12

#define ICON_GAME_UNKNOWN -1
#define ICON_OPEN_GAME 13
#define ICON_OPEN_PW_GAME 14
#define ICON_CLOSED_GAME 15
#define ICON_CLOSED_PW_GAME 16
#define ICON_STARTED_GAME 17

#define ICON_UNK_FLAG 18
#define ICON_FLAGS_BASE 19

class Battle;
class UserStatus;

class IconImageList : public wxImageList
{
  public:
    IconImageList();
     ~IconImageList();
  
    // IconImageList interface
  
    static int GetUserStateIcon( const UserStatus& us );
    static int GetRankIcon( const int& rank, const bool& showlowest = false );
    static int GetFlagIcon( const std::string& flagname );
    static int GetBattleStatusIcon( Battle& battle );
  
  protected:
    // IconImageList variables
  
};

wxImageList& icons();

#endif  //_ICONIMAGELIST_H_

