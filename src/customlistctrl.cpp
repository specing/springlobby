#include "customlistctrl.h"

BEGIN_EVENT_TABLE(customListCtrl, wxListCtrl)
#if wxUSE_TIPWINDOW
    	EVT_MOTION(customListCtrl::OnMouseMotion)
    	EVT_TIMER(IDD_TIP_TIMER, customListCtrl::OnTimer)
#endif
    	EVT_LIST_COL_BEGIN_DRAG(wxID_ANY, customListCtrl::OnStartResizeCol)
    	EVT_LEAVE_WINDOW(customListCtrl::noOp)
    	EVT_LIST_ITEM_SELECTED   ( wxID_ANY, customListCtrl::OnSelected )
        EVT_LIST_ITEM_DESELECTED ( wxID_ANY, customListCtrl::OnDeselected )
        EVT_LIST_DELETE_ITEM     ( wxID_ANY, customListCtrl::OnDeselected )
END_EVENT_TABLE()


customListCtrl::customListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pt, const wxSize& sz,long style):
					wxListCtrl (parent, id, pt, sz, style),tipTimer(this, IDD_TIP_TIMER),
					 m_selected(-1),m_selected_index(-1),m_prev_selected(-1),m_prev_selected_index(-1),
					 m_last_mouse_pos( wxPoint(-1,-1) )


{
#if wxUSE_TIPWINDOW
	m_tipwindow = NULL;
#endif
	m_tiptext = _T("BIBKJBKJB");
}

void customListCtrl::InsertColumn(long i, wxListItem item, wxString tip, bool modifiable)
{
	wxListCtrl::InsertColumn(i,item);
	colInfo temp(tip,modifiable);
	m_colinfovec.push_back(temp);
}

void customListCtrl::SetSelectionRestorePoint()
{
    m_prev_selected = m_selected;
    m_prev_selected_index = m_selected_index;
}

void customListCtrl::RestoreSelection()
{
    if ( m_prev_selected_index> -1)
    {
        SetItemState( GetIndexFromData( m_prev_selected ), wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
    }
}

void customListCtrl::OnSelected( wxListEvent& event )
{
  m_selected = GetItemData( event.GetIndex() );
  m_selected_index = event.GetIndex();
  event.Skip();
}


void customListCtrl::OnDeselected( wxListEvent& event )
{
  if ( m_selected == (int)GetItemData( event.GetIndex() )  )
    m_selected = m_selected_index = -1;
}

long customListCtrl::GetIndexFromData( const unsigned long data )
{
  for (int i = 0; i < GetItemCount() ; i++ )
  {
    if ( data == GetItemData( i ) )
      return i;
  }
  return -1;
}

long customListCtrl::GetSelectedIndex()
{
  return m_selected_index ;
}

void customListCtrl::SelectAll()
{
  for (long i = 0; i < GetItemCount() ; i++ )
  {
    SetItemState( i, wxLIST_STATE_SELECTED, -1  );
  }
}

void customListCtrl::SelectNone()
{
  for (long i = 0; i < GetItemCount() ; i++ )
  {
    SetItemState( i, wxLIST_STATE_DONTCARE, -1 );
  }
}

void customListCtrl::SelectInverse()
{
  for (long i = 0; i < GetItemCount() ; i++ )
  {
    int state = GetItemState( i, -1 );
    state = ( state == wxLIST_STATE_DONTCARE ? wxLIST_STATE_SELECTED : wxLIST_STATE_DONTCARE );
    SetItemState( i, state, -1 );
  }
}

void customListCtrl::SetSelectedIndex(const long newindex)
{
    m_selected_index = newindex;
}

long customListCtrl::GetSelectedData()
{
  return m_selected ;
}

void customListCtrl::OnTimer(wxTimerEvent& event)
{
#if wxUSE_TIPWINDOW

        if (!m_tiptext.empty())
        {
            m_tipwindow = new wxTipWindow(this, m_tiptext);
#ifndef __WXMSW__
            m_tipwindow->SetBoundingRect(wxRect(1,1,50,50));
#endif
            m_tiptext = wxEmptyString;
            tipTimer.Start(TOOLTIP_DURATION, wxTIMER_ONE_SHOT);
        }
        else
        {
            if (m_tipwindow)
                m_tipwindow->Show( false );
            m_tiptext = wxEmptyString;
            tipTimer.Stop();
        }


#endif
}

/** \todo this badly needs to be refactored, currently child classes duplicate most of this
*/
//TODO http://www.wxwidgets.org/manuals/stable/wx_wxtipwindow.html#wxtipwindowsettipwindowptr
// must have sth to do with crash on windows
//if to tootips are displayed
void customListCtrl::OnMouseMotion(wxMouseEvent& event)
{
#if wxUSE_TIPWINDOW
    //we don't want to display the tooltip again until mouse has moved
    if ( m_last_mouse_pos == event.GetPosition() )
        return;

    m_last_mouse_pos = event.GetPosition();

	if (event.Leaving())
	{
		m_tiptext = _T("");
    //TODO try thos out!!!!
//		if (m_tipwindow)
//            m_tipwindow->Show( false );
		tipTimer.Stop();
	}
	else
	{
	    if (tipTimer.IsRunning() == true)
	    {
	        tipTimer.Stop();
	    }

	    wxPoint position = event.GetPosition();

	    int flag = wxLIST_HITTEST_ONITEM;

#ifdef HAVE_WX28
    long subItem;
		long item_hit = HitTest(position, flag, &subItem);
#else
		long item_hit = HitTest(position, flag);
#endif
	    if (item_hit != wxNOT_FOUND && item_hit>=0 && item_hit<GetItemCount())
	    {

	        int coloumn = getColoumnFromPosition(position);
	        if (coloumn >= int(m_colinfovec.size()) || coloumn < 0)
	        {
	        	m_tiptext = _T("");
	        }
	        else
	        {
	        	tipTimer.Start(TOOLTIP_DELAY, wxTIMER_ONE_SHOT);
	        	m_tiptext = m_colinfovec[coloumn].first;
	        }
	    }
	}
#endif
}

int customListCtrl::getColoumnFromPosition(wxPoint pos)
{
	int x_pos = 0;
	for (int i = 0; i < int(m_colinfovec.size());++i)
	{
		x_pos += GetColumnWidth(i);
		if (pos.x < x_pos)
			return i;
	}
	return -1;
}

void customListCtrl::OnStartResizeCol(wxListEvent& event)
{
	if (!m_colinfovec[event.GetColumn()].second)
		event.Veto();
}

void customListCtrl::noOp(wxMouseEvent& event)
{
	m_tiptext = _T("");
}

