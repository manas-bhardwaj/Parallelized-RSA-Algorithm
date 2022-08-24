#include<iostream>    //for input and output
#include<conio.h>     //for console input and output
#include<fstream>     //for file manipulation
#include<windows.h>   //used for system cls function(clear screen)
#include<stdlib.h>    //for macros and general functions
#include<omp.h>       //for using OpenMP
#include<math.h>      //for mathematical operations like square roots

#define thr 8         //setting number of threads to be used for parallelization

using namespace std;

//initializing all the variables used in the code
long int p=0, q=0, n=0, t=0, flag=0, e[10000]= {0}, d[10000]= {0}, temp[10000]= {0}, j=0, m[10000]= {0}, en[10000]= {0}, i=0, r=0;
string msg="";

//functions declarations for functions that are defined later
int prime(long int);
void ce();
void encrypt();
void decrypt();

//function to display the loading animation
void loadupscreen()
{
    string st;
    fstream fa("asciiart.txt");    //loading the file containing the contents to be displayed on startup

    //reading the file contents and displaying them
    while(fa)
    {
        if(fa.eof())
        {
            break;
        }
        getline(fa,st);
        cout<<st<<"\n";
        Sleep(100);
    }
    fa.close();         //closing the file object
    getch();            //waiting for keypress to clear the screen
    system("CLS");
}

//function to display the main menu and take user input to call various functions
void dispmenu()
{
    cout<<R"(
    _  _       _  _     __  __                      _  _       _  _
  _| || |_   _| || |_  |  \/  | ___ _ __  _   _   _| || |_   _| || |_
 |_  ..  _| |_  ..  _| | |\/| |/ _ \ '_ \| | | | |_  ..  _| |_  ..  _|
 |_      _| |_      _| | |  | |  __/ | | | |_| | |_      _| |_      _|
   |_||_|     |_||_|   |_|  |_|\___|_| |_|\__,_|   |_||_|     |_||_|

)";
 cout<<"\n"<<R"(
  _       _____                             _   _
 / |     | ____|_ __   ___ _ __ _   _ _ __ | |_(_) ___  _ __
 | |     |  _| | '_ \ / __| '__| | | | '_ \| __| |/ _ \| '_ \
 | |  _  | |___| | | | (__| |  | |_| | |_) | |_| | (_) | | | |
 |_| (_) |_____|_| |_|\___|_|   \__, | .__/ \__|_|\___/|_| |_|
                                |___/|_|
)";
 cout<<"\n"<<R"(
  ____        ____                             _   _
 |___ \      |  _ \  ___  ___ _ __ _   _ _ __ | |_(_) ___  _ __
   __) |     | | | |/ _ \/ __| '__| | | | '_ \| __| |/ _ \| '_ \
  / __/   _  | |_| |  __/ (__| |  | |_| | |_) | |_| | (_) | | | |
 |_____| (_) |____/ \___|\___|_|   \__, | .__/ \__|_|\___/|_| |_|
                                   |___/|_|
)";
cout<<"\n"<<R"(
  _____       _____      _ _
 |___ /      | ____|_  _(_) |_
   |_ \      |  _| \ \/ / | __|
  ___) |  _  | |___ >  <| | |_
 |____/  (_) |_____/_/\_\_|\__|

)";
cout<<R"(
  _____       _                                            _           _
 | ____|_ __ | |_ ___ _ __   _   _  ___  _   _ _ __    ___| |__   ___ (_) ___ ___
 |  _| | '_ \| __/ _ \ '__| | | | |/ _ \| | | | '__|  / __| '_ \ / _ \| |/ __/ _ \
 | |___| | | | ||  __/ |    | |_| | (_) | |_| | |    | (__| | | | (_) | | (_|  __/
 |_____|_| |_|\__\___|_|     \__, |\___/ \__,_|_|     \___|_| |_|\___/|_|\___\___|
                             |___/
)";
}

//function for encryption and decryption key pair generation
void ce()
{
    int k;
    k = 0;
    bool skip = false;           //creating a boolean variable to control loop exit to match openMP standards
    omp_set_dynamic(0);          //disable dynamic adjustments of thread allocation by compiler
    omp_set_num_threads(thr);    //setting the number of threads to be used by OpenMP(declared above as global variable)

    //starting the parallel region to find keypairs
    #pragma omp parallel for firstprivate(k)
    for (i = 2; i < t; i++)
    {
        if(skip) continue;

        //skip if totient is divisible by number
        if (t % i == 0)
            continue;

        flag = prime(i);   //checking if the number is prime

        //loop to find the decryption key for every corresponding encryption key
        if (flag == 1 && i != p && i != q && i!=r)
        {
            e[k] = i;    //encryption key

            //to find the value of d, the condition to be satisfied is
            //e*d = 1 mod(totient)
            long int ed = 1;    //setting e*d = 1 initially
            while (1)
            {
                ed = ed + t;    //adding t to e*d every iteration so that the RHS of above condition is valid

                //checking if d is an integer or not
                if (ed % e[k] == 0)
                {
                    flag = (ed / e[k]);
                    break;
                }
            }

            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                skip = true;
        }
    }
}

//function for encrypting the message and generating an encrypted text file
void encrypt()
{
 system("CLS");
    cout<<"\n"<<R"(
  _       _____       _              _   _            _            _                                     _  __
 / |     | ____|_ __ | |_ ___ _ __  | |_| |__   ___  | |_ _____  _| |_   _   _  ___  _   _ _ __ ___  ___| |/ _|
 | |     |  _| | '_ \| __/ _ \ '__| | __| '_ \ / _ \ | __/ _ \ \/ / __| | | | |/ _ \| | | | '__/ __|/ _ \ | |_
 | |  _  | |___| | | | ||  __/ |    | |_| | | |  __/ | ||  __/>  <| |_  | |_| | (_) | |_| | |  \__ \  __/ |  _|
 |_| (_) |_____|_| |_|\__\___|_|     \__|_| |_|\___|  \__\___/_/\_\\__|  \__, |\___/ \__,_|_|  |___/\___|_|_|
                                                                         |___/
)";
    cout<<"\n"<<R"(
  ____        _   _                    _            _      __ _ _
 |___ \      | | | |___  ___    __ _  | |_ _____  _| |_   / _(_) | ___
   __) |     | | | / __|/ _ \  / _` | | __/ _ \ \/ / __| | |_| | |/ _ \
  / __/   _  | |_| \__ \  __/ | (_| | | ||  __/>  <| |_  |  _| | |  __/
 |_____| (_)  \___/|___/\___|  \__,_|  \__\___/_/\_\\__| |_| |_|_|\___|

)";
cout<<R"(
  _____       _                                            _           _
 | ____|_ __ | |_ ___ _ __   _   _  ___  _   _ _ __    ___| |__   ___ (_) ___ ___
 |  _| | '_ \| __/ _ \ '__| | | | |/ _ \| | | | '__|  / __| '_ \ / _ \| |/ __/ _ \
 | |___| | | | ||  __/ |    | |_| | (_) | |_| | |    | (__| | | | (_) | | (_|  __/
 |_____|_| |_|\__\___|_|     \__, |\___/ \__,_|_|     \___|_| |_|\___/|_|\___\___|
                             |___/
)";
    int opt;
    string tempstring;
    cin>>opt;
    if(opt == 1)
      {
       system("CLS");
       cout<<R"(
  _____       _              _   _            _            _
 | ____|_ __ | |_ ___ _ __  | |_| |__   ___  | |_ _____  _| |_
 |  _| | '_ \| __/ _ \ '__| | __| '_ \ / _ \ | __/ _ \ \/ / __|
 | |___| | | | ||  __/ |    | |_| | | |  __/ | ||  __/>  <| |_
 |_____|_| |_|\__\___|_|     \__|_| |_|\___|  \__\___/_/\_\\__|

)";
       getline(cin,tempstring);
       getline(cin,tempstring);
       fstream crtinput("Input.txt",ios::out);
       crtinput<<tempstring;
       crtinput.close();
       system("CLS");
      }
    msg="";
    ifstream fin("Input.txt",ios::in);
    string tp;
    while(fin)
         {
          if(fin.eof())
            {
             break;
            }
          getline(fin,tp);
          msg.append(tp);
         }
    fin.close();
    system("CLS");
    cout<<"\n"<<R"(
  _____ _             __  __                                   _
 |_   _| |__   ___   |  \/  | ___  ___ ___  __ _  __ _  ___   (_)___
   | | | '_ \ / _ \  | |\/| |/ _ \/ __/ __|/ _` |/ _` |/ _ \  | / __|
   | | | | | |  __/  | |  | |  __/\__ \__ \ (_| | (_| |  __/  | \__ \
   |_| |_| |_|\___|  |_|  |_|\___||___/___/\__,_|\__, |\___|  |_|___/
                                                 |___/
)"<<"\n";
    cout<<msg;
    double tstart = omp_get_wtime();    //recording the starting timestamp for encryption process
    for(i = 0; msg[i] != '\0'; i++)
    {
     m[i] = msg[i];
    }

    //finding value of n and totient
    n = p * q * 2;
    t = (p - 1) * (q - 1) * (r-1);
    ce();    //calling the keypair generator function

    long int pt, ct, key = e[10], k, len;
    len = msg.length();

    //loop to encrypt the entire string data
    for(i=0;i < len;i++)
    {
        pt = m[i];
//        pt = pt - 96;
        k = 1;

        //loop to encrypt each individual character
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
//        ct = k + 96;
        ct = k;
        en[i] = ct;
    }
    en[i] = -1;
    double tend = omp_get_wtime();    //recording the ending timestamp for encryption process
    cout<<R"(
  _____ _                                              _           _                                                _
 |_   _| |__   ___     ___ _ __   ___ _ __ _   _ _ __ | |_ ___  __| |   _ __ ___   ___  ___ ___  __ _  __ _  ___   (_)___
   | | | '_ \ / _ \   / _ \ '_ \ / __| '__| | | | '_ \| __/ _ \/ _` |  | '_ ` _ \ / _ \/ __/ __|/ _` |/ _` |/ _ \  | / __|
   | | | | | |  __/  |  __/ | | | (__| |  | |_| | |_) | ||  __/ (_| |  | | | | | |  __/\__ \__ \ (_| | (_| |  __/  | \__ \
   |_| |_| |_|\___|   \___|_| |_|\___|_|   \__, | .__/ \__\___|\__,_|  |_| |_| |_|\___||___/___/\__,_|\__, |\___|  |_|___/
                                           |___/|_|                                                   |___/
)"<<"\n";
    ofstream fcd;
    fcd.open("Encrypted.txt",ios::out);
    ofstream ftmp;
    ftmp.open("Temp.txt",ios::out);

    //printing the encrypted message
    for (i = 0; en[i] != -1; i++)
        {
         printf("%ld ", en[i]);
         fcd<<en[i];
         fcd<< " ";
         ftmp<<temp[i]<<" ";
        }
    fcd<<"-1";
    fcd.close();
    ftmp.close();
    cout<<"\n\n"<<R"(
  _____ _                  _____     _
 |_   _(_)_ __ ___   ___  |_   _|_ _| | _____ _ __    _
   | | | | '_ ` _ \ / _ \   | |/ _` | |/ / _ \ '_ \  (_)
   | | | | | | | | |  __/   | | (_| |   <  __/ | | |  _
   |_| |_|_| |_| |_|\___|   |_|\__,_|_|\_\___|_| |_| (_)

)";
  //printing the time taken for the encryption process
  cout<<"End "<<tend;
  cout<<"\nStart "<<tstart;
  cout<<"\nDiff "<<(double)(tend-tstart);
}

//function to decrypt the encrypted message
void decrypt()
{
    //finding the values of n, totient, encryption and decryption keys
    n = p * q * 2;
    t = (p - 1) * (q - 1) * (r-1);
    ce();
    system("CLS ");
    string st,st1;
    ifstream fcdc,ftmp;
    i=0;
    fcdc.open("Encrypted.txt",ios::in);
    ftmp.open("Temp.txt",ios::in);
    cout<<"\n"<<R"(
  _____ _                                              _           _     __ _ _                         _        _
 |_   _| |__   ___     ___ _ __   ___ _ __ _   _ _ __ | |_ ___  __| |   / _(_) | ___     ___ ___  _ __ | |_ __ _(_)_ __  ___
   | | | '_ \ / _ \   / _ \ '_ \ / __| '__| | | | '_ \| __/ _ \/ _` |  | |_| | |/ _ \   / __/ _ \| '_ \| __/ _` | | '_ \/ __|
   | | | | | |  __/  |  __/ | | | (__| |  | |_| | |_) | ||  __/ (_| |  |  _| | |  __/  | (_| (_) | | | | || (_| | | | | \__ \
   |_| |_| |_|\___|   \___|_| |_|\___|_|   \__, | .__/ \__\___|\__,_|  |_| |_|_|\___|   \___\___/|_| |_|\__\__,_|_|_| |_|___/
                                           |___/|_|
)"<<"\n";
    //displaying the content of the encrypted file taken as input
    while(fcdc)
    {
        if(fcdc.eof())
        {
            break;
        }
        fcdc>>st;
        ftmp>>st1;
        en[i]=stol(st);
        cout<<en[i]<<" ";
        if(en[i]!=-1)
          {
           temp[i]=stol(st1);
          }
     i++;
    }
    fcdc.close();
    ftmp.close();
    long int pt, ct, key = d[10], k;
    int zxc;
    /*Since openMP doesnt allow dynamic loop termination condition
    therefore we finds the termination value for the decryption loop */
    for(zxc = 0; en[zxc] != -1; zxc++);

    //loop for decrypting entire message
    for (i=0;i<zxc;i++)
    {
        ct = temp[i];
        k = 1;

        //loop for decrypting individual characters
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
//        pt = k + 96;
        pt = k;
        m[i] = pt;
    }
    m[i] = -1;
    ofstream fdcd;
    fdcd.open("Decrypted.txt",ios::out);
    cout<<"\n"<<R"(
  _____ _                 _                            _           _                                                _
 |_   _| |__   ___     __| | ___  ___ _ __ _   _ _ __ | |_ ___  __| |   _ __ ___   ___  ___ ___  __ _  __ _  ___   (_)___
   | | | '_ \ / _ \   / _` |/ _ \/ __| '__| | | | '_ \| __/ _ \/ _` |  | '_ ` _ \ / _ \/ __/ __|/ _` |/ _` |/ _ \  | / __|
   | | | | | |  __/  | (_| |  __/ (__| |  | |_| | |_) | ||  __/ (_| |  | | | | | |  __/\__ \__ \ (_| | (_| |  __/  | \__ \
   |_| |_| |_|\___|   \__,_|\___|\___|_|   \__, | .__/ \__\___|\__,_|  |_| |_| |_|\___||___/___/\__,_|\__, |\___|  |_|___/
                                           |___/|_|                                                   |___/
)"<<"\n";

    //printing the decrypted message
    for (i = 0; m[i] != -1; i++)
    {
        printf("%c", m[i]);
        fdcd<<(char)m[i];
    }
    fdcd.close();
    cout<<"\n\n";
}

//function to check whether a given number is prime or not
int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

//main function
int main()
{
 loadupscreen();
 char ans = 'y';

 //setting initial prime values according to modified three key RSA
 p=47;
 q=53;
 r=31;
 do
 {
  system("CLS");
  dispmenu();
  int ch;
  cin>>ch;
  switch(ch)
        {
         case 1:encrypt();
                break;
         case 2:decrypt();
                break;
         case 3:return 0;
        }

  cout<<"\n\n"<<R"(
   ____            _   _                    ___    ____   __     __  _   ___
  / ___|___  _ __ | |_(_)_ __  _   _  ___  |__ \  / /\ \ / /    / / | \ | \ \
 | |   / _ \| '_ \| __| | '_ \| | | |/ _ \   / / | |  \ V /    / /  |  \| || |
 | |__| (_) | | | | |_| | | | | |_| |  __/  |_|  | |   | |    / /   | |\  || |
  \____\___/|_| |_|\__|_|_| |_|\__,_|\___|  (_)  | |   |_|   /_/    |_| \_|| |
                                                  \_\                     /_/
)"<<"\n";
    cin>>ans;
 }while(ans=='y' || ans =='Y');
}
