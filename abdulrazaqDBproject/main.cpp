#include <iostream>
#include <windows.h>
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/stopwatch.h>
#include <mysql.h>
#include <sstream>
#include <string>
using namespace std;

const char* hostname    = "localhost";
const char* username    = "root";
const char* password    = "";
const char* database    = "abdrazaq1";
unsigned int port       = 3306;
const char* unixsocket  = NULL;
unsigned long clientflag = 0;
wxButton* insertb;
wxButton* modifyb;
wxButton* deleteb;
wxButton* displayb;
wxButton* searchb;
wxButton* code;
wxButton* go;
const int insertbID = 100, modifybID = 101, deletebID = 102,
displayID = 103, searchID = 104, codeID=105,goID=106;
wxTextCtrl* t1;
wxTextCtrl* t2;
wxTextCtrl* t3;
wxTextCtrl* t4;
wxPanel* pan; //rubbish
wxFrame* window;
wxListCtrl *plainListView;


MYSQL* conn;
MYSQL* connectdatabase()
{

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
    //conn = mysql_real_connect(conn, "localhost", "root", "", "abdrazaq1", 0, NULL, 0);
    if(conn)
    {
        cout<<"connected to database "<<endl;
        return conn;
    }
    else
    {
        cout<<"Failed to connect to database"<<endl;
        return conn;
    }
}


class frame: public wxFrame
{

    public:
  wxTimer m_timer;
  void OnTimer(wxTimerEvent& event)
{
    modifyb->GetParent()->InvalidateBestSize();
    modifyb->GetParent()->Layout();
}
void OnIdle(wxIdleEvent& event)
{
    modifyb->GetParent()->InvalidateBestSize();
    modifyb->GetParent()->Layout();
}


 frame() : wxFrame(NULL, wxID_ANY, "GUI", wxDefaultPosition, wxSize(800, 540))
{
    m_timer.SetOwner(this, 10);
    m_timer.Start(1000);  // 1000ms = 1s
    Connect(10, wxEVT_TIMER, wxTimerEventHandler(frame::OnTimer));
    Connect(wxEVT_IDLE, wxIdleEventHandler(frame::OnIdle));
}

};

class App : public wxApp
{
    public:
bool OnInit()  // = main method
    {
        MYSQL* conn = connectdatabase();

        window = new frame();


        t1 = new wxTextCtrl(window, wxID_ANY,"",wxPoint(0,180),   wxSize(120,30));
        t2 = new wxTextCtrl(window, wxID_ANY,"",wxPoint(121,180), wxSize(120,30));
        t3 = new wxTextCtrl(window, wxID_ANY,"",wxPoint(242,180), wxSize(120,30));

        t1->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, 600));
        t2->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, 600));
        t3->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, 600));

        t4 = new wxTextCtrl(window, wxID_ANY,"",wxPoint(0,325),   wxSize(360,30));
        t4->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, 600));
        t4->Hide();

        insertb = new wxButton(window, insertbID, "Insert",wxPoint(0, 60), wxSize(140, 30));
        insertb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        insertb->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        //insertb->SetBitmap();
        //insertb->SetWindowStyle( wxBORDER_THEME );
//        Button4 = new wxCustomButton(window,ID_BUTTON4,"test",wxBitmap(wxImage(_T("C:\\Users\\sw\\Desktop\\zTest Window\\blueButton.png"))),wxPoint(24,184),wxSize(256,152),wxCUSTBUT_BUTTON|wxCUSTBUT_BOTTOM,wxDefaultValidator,_T("ID_BUTTON4"));
  //  Button4->SetBitmapSelected(wxBitmap(wxImage(_T("C:\\Users\\sw\\Desktop\\zTest Window\\selectedBlueButton.png"))));
    //Button4->SetBitmapDisabled(Button4->CreateBitmapDisabled(Button4->GetBitmapLabel()));



        modifyb = new wxButton(window, modifybID, "Modify",wxPoint(141, 60), wxSize(140, 30));
        modifyb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        modifyb->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        deleteb = new wxButton(window, deletebID, "Delete",wxPoint(282, 60), wxSize(140, 30));
        deleteb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        deleteb->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        displayb = new wxButton(window, displayID, "Display",wxPoint(423, 60), wxSize(140, 30));
        displayb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        displayb->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        searchb = new wxButton(window, searchID, "Filter",wxPoint(0, 220), wxSize(120, 30));
        searchb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        searchb->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        code = new wxButton(window, codeID, "Code",wxPoint(0, 295), wxSize(80, 30));
        code->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        code->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        go = new wxButton(window, goID, "Go",wxPoint(10, 365), wxSize(40, 30));
        go->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        go->SetFont(wxFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        go->Hide();

        //////////////////displayb->Raise();

        //  wxInitAllImageHandlers();

      // Create the panel and set the background color to white
 //       wxPanel* panel = new wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(800, 400));

 //       panel->SetBackgroundColour(*wxWHITE);

        // Load the image file and create a wxStaticBitmap object
     //   wxBitmap bgBitmap("double-color-futuristic-neon.png", wxBITMAP_TYPE_PNG);
   //     wxStaticBitmap* background = new wxStaticBitmap(panel, wxID_ANY, bgBitmap,wxDefaultPosition ,wxSize(800,400));

        // Fit the frame size to the image size
       // window->SetClientSize(bgBitmap.GetWidth(), bgBitmap.GetHeight());
     //   panel->Lower();


        wxImage::AddHandler(new wxPNGHandler);
       // wxBitmap bgBitmap("double-color-futuristic-neon.png", wxBITMAP_TYPE_PNG);
        wxBitmap bgBitmap("redalert.png", wxBITMAP_TYPE_PNG);
        wxStaticBitmap* background = new wxStaticBitmap(window, wxID_ANY, bgBitmap);

       // window->SetClientSize(bgBitmap.GetWidth(), bgBitmap.GetHeight());

        wxStaticText* text = new wxStaticText(window, wxID_ANY, "      ID            Name       Country",
                                              wxPoint(0,140), wxSize(300,20), wxALIGN_CENTRE_HORIZONTAL);
        text->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        text->SetBackgroundColour(wxColor(213, 55, 67));



        //wxPanel *panel_bottom = new wxPanel(window, wxID_ANY, wxDefaultPosition, wxSize(400, 20));
        //panel_bottom->SetBackgroundColour(wxColor(0, 0, 255));
       // sizer->Add(panel_bottom, 1, wxALIGN_CENTER);
   // wxSizer *sizer_bottom = new wxBoxSizer(wxVERTICAL);
   // wxSizer *sizer_centering = new wxBoxSizer(wxHORIZONTAL);

    window->CreateStatusBar();
// Bind button press and release events
    insertb->Bind(wxEVT_LEFT_DOWN, &App::OnButtonPressed, this);
    modifyb->Bind(wxEVT_LEFT_DOWN, &App::OnButtonPressed, this);
    deleteb->Bind(wxEVT_LEFT_DOWN, &App::OnButtonPressed, this);
    displayb->Bind(wxEVT_LEFT_DOWN, &App::OnButtonPressed, this);
    searchb->Bind(wxEVT_LEFT_DOWN, &App::OnButtonPressed, this);
    code->Bind(wxEVT_LEFT_DOWN, &App::OnButtonPressed, this);
    go->Bind(wxEVT_LEFT_DOWN, &App::OnButtonPressed, this);

    insertb->Bind(wxEVT_LEFT_UP, &App::OnButtonReleased, this);
    modifyb->Bind(wxEVT_LEFT_UP, &App::OnButtonReleased, this);
    deleteb->Bind(wxEVT_LEFT_UP, &App::OnButtonReleased, this);
    displayb->Bind(wxEVT_LEFT_UP, &App::OnButtonReleased, this);
    searchb->Bind(wxEVT_LEFT_UP, &App::OnButtonReleased, this);
    code->Bind(wxEVT_LEFT_UP, &App::OnButtonReleased, this);
    go->Bind(wxEVT_LEFT_UP, &App::OnButtonReleased, this);

    this->Bind(wxEVT_KEY_DOWN, &App::onCTRL, this);

    window->Show();

    addPlainList();


    return true;
    }

void onCTRL(wxKeyEvent& evt)
{
    if (evt.GetKeyCode() == 308) //ctrl is pressed
    {
    wxLogStatus("ctrl was pressed!");
    displayb->Refresh();
    deleteb->Refresh();
    modifyb->Refresh();
    insertb->Refresh();
    searchb->Refresh();
    code->Refresh();
    go->Refresh();
    t1->Refresh();
    t2->Refresh();
    t3->Refresh();
    t4->Refresh();
    plainListView->DeleteAllItems();
    display();
    this->Unbind(wxEVT_KEY_DOWN, &App::onCTRL, this);

    } else{ wxLogStatus("");}
}


 void OnButtonPressed(wxMouseEvent& event)
{
    insertb->SetForegroundColour(wxColour(0, 0, 0));  // black  //test

}

 void OnButtonReleased(wxMouseEvent& event)
{
    if     ( insertbID == event.GetId())
    {
    insertion();
    insertb->SetBackgroundColour(wxColour(255, 0, 0));    //red
    modifyb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    deleteb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    displayb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    searchb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    code->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    go->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    resetTF();
    plainListView->DeleteAllItems();
    display();
    }
    else if( modifybID == event.GetId())
    {
    modify();
    insertb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    modifyb->SetBackgroundColour(wxColour(255, 0, 0));    //red
    deleteb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    displayb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    searchb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    code->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    go->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    resetTF();
    plainListView->DeleteAllItems();
    display();
    }
    else if( deletebID == event.GetId())
    {
    delete1();
    insertb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    modifyb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    deleteb->SetBackgroundColour(wxColour(255, 0, 0));    //red
    displayb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    searchb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    code->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    go->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    resetTF();
    plainListView->DeleteAllItems();
    display();

    }
    else if(displayID == event.GetId())
    {
        insertb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        modifyb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        deleteb->SetBackgroundColour(wxColour(60, 90, 200));  //blue
        displayb->SetBackgroundColour(wxColor(255, 0, 0));   //red
        searchb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        code->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        go->SetBackgroundColour(wxColor(60, 90, 200));   //blue
        plainListView->DeleteAllItems();
        display();
        wxLogStatus("displayed...");
    }
    else if( searchID == event.GetId())
    {
    plainListView->DeleteAllItems();
    search1();
    insertb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    modifyb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    deleteb->SetBackgroundColour(wxColour(60, 90, 200));    //blue
    displayb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    searchb->SetBackgroundColour(wxColor(255, 0, 0));     //red
    code->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    go->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    resetTF();

    }
    else if(codeID == event.GetId())
    {
    doCode();
    insertb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    modifyb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    deleteb->SetBackgroundColour(wxColour(60, 90, 200));    //blue
    displayb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    searchb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    code->SetBackgroundColour(wxColor(255, 0, 0));      //red
    go->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    }
    else if(goID == event.GetId())
    {
    doGo();
    insertb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    modifyb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    deleteb->SetBackgroundColour(wxColour(60, 90, 200));    //blue
    displayb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    searchb->SetBackgroundColour(wxColor(60, 90, 200));   //blue
    code->SetBackgroundColour(wxColor(60, 90, 200));      //blue
    go->SetBackgroundColour(wxColor(255, 0, 0));      //red

    }

}
 void resetTF()
      {
          t1->SetLabelText("");
          t2->SetLabelText("");
          t3->SetLabelText("");
      }

 void insertion()
      {
    int qstate = 0;
    stringstream ss;
    int id;
    string name,category, idStr;

    idStr =t1->GetValue();
    id = wxAtoi(idStr);
    name = t2->GetValue();
    category = t3->GetValue();

    ss << "INSERT INTO RedAlert3 (id, name, country) VALUES ('"+idStr+"', '"+name+"', '"+category+"')";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0)
    {
        wxLogStatus("Record inserted...");
    }
    else{
        wxLogStatus("failed to insert___");
    }

      }

  void modify()
  {
    int qstate = 0;
    stringstream ss;
    int id;
    string name,category, idStr;

    idStr =t1->GetValue();
    id = wxAtoi(idStr);
    name = t2->GetValue();
    category = t3->GetValue();

    ss << "UPDATE RedAlert3 SET name ='"+ name+"',country ='"+category+"' WHERE id ="+idStr;
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0)
    {
        wxLogStatus("Record modified...");
    }
    else{
        wxLogStatus("failed to modify___");
    }

  }
  void delete1()
  {
    string idStr;
    stringstream ss;
    long  s = myGetSelection();
    if(s==-1) {wxLogStatus("failed to delete___"); return;}
    idStr= plainListView->GetItemText(s, 0);

    ss  << "DELETE FROM RedAlert3 WHERE id = "+ idStr;
    string query = ss.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);
    if(qstate == 0){
        wxLogStatus("Record deleted...");
    }

  }
  long myGetSelection()
{
    long n = plainListView->GetItemCount();
    long i;
    for (i = 0; i < n; i++)
    {
        if (plainListView->GetItemState(i, wxLIST_STATE_SELECTED) & wxLIST_STATE_SELECTED)
        {
            return i;
        }
    }
    return -1;
}
  void addPlainList()
{
    plainListView = new wxListCtrl(window, wxID_ANY, wxPoint(490,100), wxSize(300, 400), 0x20);
    plainListView->Raise();

    plainListView->AppendColumn("");
    plainListView->AppendColumn("");
    plainListView->AppendColumn("");

    wxStaticText* text2 = new wxStaticText(window, wxID_ANY, "ID       Name      Country",
                                              wxPoint(490,95), wxSize(300,5), wxALIGN_CENTRE_HORIZONTAL);
        text2->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        text2->SetBackgroundColour(wxColor(213, 55, 67));


    plainListView->SetColumnWidth(0, 80);
    plainListView->SetColumnWidth(1, 110);
    plainListView->SetColumnWidth(2, 110);
}
void populatePlainListView(string id, string name, string country)
{

        int insertionPoint = plainListView->GetItemCount();

        plainListView->InsertItem(insertionPoint, id);
        plainListView->SetItem(insertionPoint, 1, name);
        plainListView->SetItem(insertionPoint, 2, country);
}
void display()
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM redalert3");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                {
                    populatePlainListView(row[0],row[1],row[2]);
                }
        }
    }
    else
        {
        wxLogStatus("Failed to fetch___");
        }
}
void search1()
{
     MYSQL_ROW row;
     MYSQL_RES* res;
     if(conn){
        string name, country, idStr;
        stringstream ss;
        idStr = t1->GetValue();
        name = t2->GetValue();
        country = t3->GetValue();

        if (name != "")
        {     ss<< "SELECT * FROM redalert3 where name like '"+name+"%'";}
        else if (country != ""){ ss<< "SELECT * FROM redalert3 where country like '"+country+"%'";}
        else if (idStr != ""){   ss<< "SELECT * FROM redalert3 where id like '"+idStr+"%'";}
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                    populatePlainListView(row[0],row[1],row[2]);
            }
            wxLogStatus("searching done...");
        }
    }
    else
        {
        wxLogStatus("Failed to search____");
        }
}
void doCode()
{
    t4->Show();
    go->Show();
}
void doGo()
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    string query;
    plainListView->DeleteAllItems();
    query= t4->GetValue();

    if(conn){

        const char* q = query.c_str();
        int qstate = mysql_query( conn,q );
        string idd="",name="", country="";


        if(!qstate){
           if(query.find("where")!=4294967295){query.erase(query.begin() +query.find("where") , query.end() );}
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                    if(res->field_count== 3)
                    {

                        if( query.find("id")!=4294967295){idd = row[0];}
                        if(query.find("name")!=4294967295){name= row[1];}
                        if(query.find("country")!=4294967295){country= row[2];}
                        populatePlainListView(idd,name,country);


                    }

                    else if(res->field_count== 2)
                    {
                        if(query.find("id")!=4294967295&& query.find("name")!=4294967295){idd = row[0]; name = row[1];}
                        if(query.find("id")!=4294967295&& query.find("country")!=4294967295){idd = row[0]; country = row[1];}
                        if(query.find("country")!=4294967295&& query.find("name")!=4294967295){name = row[0]; country = row[1];}
                        populatePlainListView(idd,name,country);

                    }
                    else if(res->field_count== 1)
                    {
                        if(query.find("id")!=4294967295 ){idd = row[0];}
                        if( query.find("country")!=4294967295){country = row[0];}
                        if( query.find("name")!=4294967295){name = row[0];}

                        populatePlainListView(idd,name,country);
                    }

            }

        }
    }
    else
        {
        wxLogStatus("Failed to excecute___");
        }
}

};


wxIMPLEMENT_APP(App);


