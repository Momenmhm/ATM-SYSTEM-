#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std ;

const string Fpath = "clientinfo1.txt" ;

enum eMainMenu { Quick_withdraw = 1 , Normal_withdraw = 2 , Deposit = 3 , Show_balance = 4 , LogOut = 5 }  ; 

enum eQuickWithdrawMenu { s20 = 1 , s50 = 2 , s100 = 3 , s200 = 4 , s400 = 5 , s600 = 6 , s800 = 7 , s1000 = 8 , sExit = 9 };

struct stClient {
    
    string AccountNum;
    string PinCode;
    string Name ;
    string Phone;
    string Balance ;
}; 

stClient Client ; 

void MainMenu() ; 
void QuickWithdraw (short) ; 
void QuickWithdrawMenu ();
void LoginMenu() ; 
int ClientBalance () ;


vector<string> split (string str , string space = "#//#") {
   
    string sword ="";
    vector<string> strInfo ;
    short pos =0;
    
    // find the separator and save index in pos 
    while ((pos = str.find(space)) != std :: string ::npos){
        
    //  cut the word and save it in vector 
        sword = str.substr(0, pos);
        if (sword != ""){
            strInfo.push_back(sword) ;
        }
        str.erase(0 , pos + space.length());
        
    }
    
    // because the condition at while loop there a word well left in string str 
    if (str != "")
        strInfo.push_back(str) ;
        
    return strInfo ;
}

string JoinClient ( stClient strInfo , string space ="#//#"){
  
    string line ="";
    
    line += strInfo.AccountNum + space ;
    line += strInfo.PinCode + space ;
    line += strInfo.Name + space ;
    line += strInfo.Phone + space ;
    line += strInfo.Balance ;
    
    return line ;  
}

stClient ChangDateToStruct(vector<string>vstr){
        
    stClient Client ;
    
    if (vstr.size() >= 4){
        
        Client.AccountNum = vstr[0] ;
        Client.PinCode = vstr[1] ;
        Client.Name = vstr[2] ;
        Client.Phone = vstr[3] ;
  //      Client.Balance = stod(vstr[4]) ;    
        Client.Balance = vstr[4];
    }
    return Client ;          
}

vector<stClient> LoadClientFromFile(  ){
    
    vector<stClient> vclients ;
    fstream myfile ;
    string line ;
    myfile.open(Fpath , ios :: in);

    if (myfile.is_open()){

        while (getline(myfile , line)){
            
            vclients.push_back(ChangDateToStruct(split(line)));                        
        } 
        myfile.close();              
    }  
    return  vclients ;  
}


void SaveClientsToFile(vector<stClient>& vClients){
    
    fstream myfile ;
    
    myfile.open(Fpath , ios :: out);
    
    if(myfile.is_open()){
        
        for (stClient& c : vClients ){            

                myfile << JoinClient(c) << endl ;
        }        
    }
    myfile.close();        
}

bool FindClient (string AccountNum, vector<stClient> vClients, stClient& client ){
    
    for (stClient & C : vClients){
        
        if (AccountNum == C.AccountNum){
            
            client = C ;
            return true ;
        }
    }    
    return false ;
}

short ReadChoice (string msg, short validate){
    
    short choice =0;
    do{
    cout << msg ; 
    
    cin >> choice ; 
    } while (choice > validate || choice < 1 ); 
    return choice ; 
    
}

void BackToMainMenu (){
    
    MainMenu ();
}

void WithdrawToClient (int amount ){
    
    vector<stClient> vClients = LoadClientFromFile() ; 
    for ( stClient & c : vClients ){
        
        if (Client.AccountNum == c.AccountNum){
            c.Balance = to_string( stoi(c.Balance) - amount) ; 
            Client = c ;
            SaveClientsToFile (vClients); 
            return ; 
        }
    }    
}

void TakeQuickWithdrawAction( short choice ){
    
//    system ("clear");
    switch ( choice ){
        
        case eQuickWithdrawMenu :: s20  :{
            
            QuickWithdraw(20);
            QuickWithdrawMenu ();
            break ; 
        }
        case eQuickWithdrawMenu :: s50 :{
            
            QuickWithdraw(50);
            QuickWithdrawMenu ();
            break ; 
        }
       case  eQuickWithdrawMenu :: s100 : {
        
            QuickWithdraw(100);
            QuickWithdrawMenu ();
            break ; 
       }
       case  eQuickWithdrawMenu :: s200 :{
                     
           QuickWithdraw(200);
           QuickWithdrawMenu ();
           break ; 
       }
       
       case eQuickWithdrawMenu :: s400 : {
                
           QuickWithdraw(400); 
           QuickWithdrawMenu ();     
           break ; 
       }      
        case eQuickWithdrawMenu :: s600 : {
            
           QuickWithdraw(600);     
           QuickWithdrawMenu ();                    
           break ; 
       }       
       case eQuickWithdrawMenu :: s800 : {
          
           QuickWithdraw (800)  ;  
           QuickWithdrawMenu ();          
           break ; 
       }       
       case eQuickWithdrawMenu :: s1000 : {
          
          QuickWithdraw(1000);   
          QuickWithdrawMenu ();                           
           break ; 
       }  
      case eQuickWithdrawMenu :: sExit : {
         BackToMainMenu();                                 
          break ; 
       }         
    }    
}

void QuickWithdrawScreen(){
    system("clear");
     cout <<"\n---------------------------------------\n";
    cout << "          QUICK WITHDRAW SCREEN               ";
    cout << "\n--------------------------------------\n" ;     
    
}

void QuickWithdrawMenu (){
    
    QuickWithdrawScreen(); 
    cout <<"\N enter the amount to withdraw : "; 
    cout <<"\n [1]. 20    [2]. 50 ";
    cout <<"\n [3]. 100     [4]. 200  " ; 
    cout <<"\n [5]. 400     [6]. 600   ";
    cout <<"\n [7]. 800     [8]. 1000 ";
    cout <<"\n [9]. EXIT ";  
    
    TakeQuickWithdrawAction((eQuickWithdrawMenu) ReadChoice ("\n enter a number between [1-9] : ", 9));
}

void QuickWithdraw (short amount){
    
    char answer ;
     cout <<"\n Are you sure to witdraw amount [ "<< abs(amount) <<" ] ? (y/n)"; 
     cin >> answer ; 
     if ( stod(Client.Balance) < amount  ){
         cout <<"\n the balance less than amount ! \n\n";
         system ("pause");
         return ; 
         
     }
     if(tolower(answer) == 'y'){
         WithdrawToClient(amount); 
         cout<<"\n withdraw successfully ";
         cout <<"\n your balance is : "<< ClientBalance() ;
         cout <<endl << endl ;
         system ("pause");
     }      
} 


int ClientBalance (){
    
    return stod(Client.Balance); 
}

void ShowClientBalace (){
    
    system("clear");
     cout <<"\n---------------------------------------\n";
    cout << "          BALANCE SCREEN               ";
    cout << "\n--------------------------------------\n" ;  
    cout <<"\n your balance is : "<<ClientBalance();
    cout << "\n--------------------------------------\n" ;  
    
    cout << endl ; 
    system ("pause"); 
    
}

void NormalWithdraw (){
    
    system("clear");
     cout <<"\n---------------------------------------\n";
    cout << "        NORMAL WITHDRAW SCREEN               ";
    cout << "\n--------------------------------------\n" ;  
    
    short amount =0;
    
    cout <<"\n enter amount to withdraw and *5 ";
    cin >> amount ; 
    if ( amount %5 != 0 ){
        cout <<"\n amount not revolte of 5 \n\n";
        system ("pause"); 
          
    }
    else {
        QuickWithdraw(amount ); 
    }  
}

void DepositToClient ( ){
    
    system("clear");
     cout <<"\n---------------------------------------\n";
    cout << "         DEPOSIT SCREEN               ";
    cout << "\n--------------------------------------\n" ;  
    
    short amount =0;
    
    cout <<"\n enter amount to deposit "; 
    cin >> amount ; 
    
    if (amount > 0 ){
        QuickWithdraw(amount *-1); 
    }
    else {
        cout <<"\n amount must not be negative! ";
    }

}


void TakeAction( short choice ){
    
//    system ("clear");
    switch ( choice ){
        
        case eMainMenu :: Quick_withdraw :{
            
            QuickWithdrawMenu();
            BackToMainMenu();
            break ; 
        }
        case eMainMenu :: Normal_withdraw :{
            
            NormalWithdraw();
            BackToMainMenu();
            break ; 
        }
       case  eMainMenu :: Deposit: {
        
            DepositToClient();
            BackToMainMenu();
            break ; 
       }
       case  eMainMenu :: Show_balance :{
           
           ShowClientBalace();
           BackToMainMenu();
           break ; 
       }
       
       case eMainMenu :: LogOut : {
                     
           LoginMenu( ) ; 
           break ; 
       }
       
    }
    
}


void MainMenu(){
    
    system("clear");
    cout <<"\n----------------------------------\n";
    cout << "              Main menu               ";
    cout << "\n----------------------------------\n" ;
    cout << "\n    [1]. Quick Withdraw " ;
    cout << "\n    [2]. Normal Withdraw ";
    cout << "\n    [3]. Deposit ";
    cout << "\n    [4]. Show Balance";
    cout << "\n    [5]. logout " ; 
    cout << "\n----------------------------------" << endl; 
    
    TakeAction((eMainMenu) ReadChoice (" enter a choice between [1-5]" , 5));
                  
}

void LoginScreen(){
    
    system("clear");
     cout <<"\n----------------------------------\n";
    cout << "           LOGIN SCREEN               ";
    cout << "\n----------------------------------\n" ;     
}

void ReadClientInfo (string& AccountNum , string& PinCode ){
    
    cout <<"\n enter the account number : ";
    getline ( cin >> ws, AccountNum);
    cout << " enter user pin code : ";
    getline ( cin >> ws, PinCode);    
}

void LoginMenu( ){
    
    LoginScreen();
    string AccountNum , PinCode ; 
    vector<stClient> vClients = LoadClientFromFile() ; 
         
    ReadClientInfo(AccountNum , PinCode ); 
        
    while(! FindClient (AccountNum , vClients , Client )  ) {
        LoginScreen(); 
        cout <<"\n falid account number or pincode  "; 
        ReadClientInfo(AccountNum , PinCode ); 
    }
}

void Run_ATM_App(){
    
    LoginMenu();     
    MainMenu () ; 
    
}

int main(){
    
    Run_ATM_App(); 
    
    return 0 ; 
}
