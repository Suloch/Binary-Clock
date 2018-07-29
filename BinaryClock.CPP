#include<time.h>      // for the time differnece
#include <iostream.h>
#include <conio.h>
#include<process.h>
#include<fstream.h>       //using the file handling
#include<stdio.h>         // for gets() and puts()

class bclock
{
 int i, j;            //counters
 char tbl[9][13];     //grid for printing the output
 float tym;
 char chc;

 void switch_(int, int);      //this function switches a point on/off by putting '*' at the required position 
 void allocate(int, int);     //this function decides which point should be on/off

 public :
 bclock();            
 int sec, min, hr;            // variables for calculating time time
 struct rem{                  //this variables store data for the reminder
 int Rmin, Rhr;
 char msg[50];
 }rem1;

 void count(void);            // calculates time
 void display(void);           // displays the clock and the re,minder on the screen
 void t(float);
 void detail(void);  // function to show the details of the student who submitts the project.
 };

 bclock::bclock()     //constructor for doing the rest of the job that is connecting all the peices
 {
	 detail();

  rem1.Rhr=-1;
  rem1.Rmin=-1;
  chc='y';
  float tym;

  cout<<"\nEnter current hour";
  cin>>hr;

  cout<<"\nEnter current minute";
  cin>>min;
  cout<<"\n Default sec=00";
  cout<<"\nWant to edit the reminder?(y/n)";
  cin>>chc;
  if(chc=='y'||chc=='Y')                  // editing the reminder
  {
     cout<<"\nEnter the message for remainder";
     gets(rem1.msg);
     cout<<"\nEnter the timing";
     cout<<"\nhour:";
     cin>>rem1.Rhr;
     cout<<"\nminute:";
     cin>>rem1.Rmin;
     ofstream fout;
     fout.open("bin.dat", ios::out|ios::binary);
     fout.write((char*)&rem1, sizeof(rem));
     fout.close();
  }
  else
  {
      ifstream fin;
      fin.open("bin.dat", ios::in|ios::binary);
      fin.read((char*)&rem1, sizeof(rem1));
 }
   for(i=0; i<9; i++)
  for(j=0; j<13; j++)
  {
    if(i%2==0)
       tbl[i][j]='-';
      else
       {
       if(j%2==0)
       tbl[i][j]='|';

       else
       tbl[i][j]=' ';
	}
  }


  for( ; ; )
  { t(1);
    display();
    count();

  }


 }


void bclock::count(void)
{
    sec++;
    if(sec==60)
    {
    sec=0;
    min++;
    }

     if(min==60)
    {
    min=0;
    hr++;
    }

    if(hr==24)
    {
    hr =0;
    }


}

void bclock::switch_(int pass, int col)
{
  switch(pass/2)
  {
  case 1 : tbl[5][col]='*';  break;
  case 2 : tbl[3][col]='*';   break;
  case 3 : tbl[3][col]='*'; tbl[5][col]='*';  break;
  case 4 : tbl[1][col]='*'; break;
  }
  if(pass%2==1)
  tbl[7][col]='*';
}


void bclock::allocate(int f, int x)
{
 int one, ten;
 one=f%10;
 ten=f/10;
 switch_(ten, x);
 switch_(one, x+2);

 }




void bclock::display(void)
{clrscr();
  if(hr==rem1.Rhr && min==rem1.Rmin)
  {
	cout<<"\n\t{~~~~~~~~~~~~~|REMINDER|~~~~~~~~~~~~~~}";
	cout<<"\n\t               --------";
	cout<<"\a\a\n\t"<<rem1.msg;
       }
 allocate(sec, 9);

 allocate(min, 5);

 allocate(hr, 1);

 for(i=0; i<9; i++)
 {
    cout<<"\n\t\t";
    for(j=0; j<13; j++)
    cout<<tbl[i][j];
  }


   for(i=0; i<9; i++)
  for(j=0; j<13; j++)
  {
    if(i%2!=0)
  {
       if(j%2!=0)
       tbl[i][j]=' ';
	}
 }
}








void bclock::t(float tym)
{
   time_t start = time(NULL);
   time_t end;
   do
   {
   end = time(NULL);
   } while(difftime(end, start) < tym );

}

 void bclock::detail(void)
 { clrscr();
   cout<<"\n\n\n\n\t\t*************************************";
   cout<<"\n\t\t* BINARY CLOCK WITH REMINDER v-1.2  *";
   cout<<"\n\t\t*************************************";

   cout<<"\n\n\tCreated by: *Your name goes here*";
   cout<<"\n\tSchool Name: ________________";
   getch();
 }


void main (void)
{
  bclock binary_clock;  //calling the constructor
  }