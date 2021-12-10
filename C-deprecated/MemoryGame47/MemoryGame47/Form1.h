#pragma once
#include "Form2.h"
#include "MessageForm.h"
#include "SetForm.h"
#include "ShopForm.h"
#include "FinderForm.h"
#include "HeroForm.h"

// Here set the parameters.
int maxr=6;
int maxc=7;
int maxk=20;
int maxsp=6;
int offset=-2; // It should be equal to the first sp index in row.h.

namespace MemoryGame47 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			this->SetStyle(static_cast<ControlStyles>(ControlStyles::AllPaintingInWmPaint |ControlStyles::DoubleBuffer |ControlStyles::UserPaint), true);
			this->UpdateStyles();

			User=new userlogin(maxk,maxsp);
			Game=new gamerules(maxr,maxc,maxk,maxsp,User->getpk(),User->getpsp()); 
			Form2 ^ UserForm=gcnew Form2(User);
			UserForm->ShowDialog();
			label1->Text=Marshal::PtrToStringAnsi((IntPtr)User->getusername());
			label2->Text=""+User->getlevel();
			Game->setlevel(User->getsave());
			label13->Text=""+User->getsave();
			if (User->getsave()!=0)
			{
				pictureBox43->Visible=false;
				pictureBox57->Visible=true;
				label6->Visible=true;
				label6->Text=""+User->getsave();
			}
			label5->Text=""+User->getcredit();
			pictureBox59->Invalidate();
			User->writefile();
			RefreshItem(false);
			// For hero system.
			Game->sethero(User->gethero());
			pictureBox56->Image=Image::FromFile(".\\heroes\\"+Game->gethero()+".png");
			pictureBox56->Enabled=true;
		}

		// Use to Decode an index into a PictureBox.
		// Input: the index that which card is clicked.
		// Output: the handle of the PictureBox.
		PictureBox ^ NtoP(int n)
		{
			switch (n)
			{
			case 0: return pictureBox1;
			case 1: return pictureBox2;
			case 2: return pictureBox3;
			case 3: return pictureBox4;
			case 4: return pictureBox5;
			case 5: return pictureBox6;
			case 6: return pictureBox7;
			case 7: return pictureBox8;
			case 8: return pictureBox9;
			case 9: return pictureBox10;
			case 10: return pictureBox11;
			case 11: return pictureBox12;
			case 12: return pictureBox13;
			case 13: return pictureBox14;
			case 14: return pictureBox15;
			case 15: return pictureBox16;
			case 16: return pictureBox17;
			case 17: return pictureBox18;
			case 18: return pictureBox19;
			case 19: return pictureBox20;
			case 20: return pictureBox21;
			case 21: return pictureBox22;
			case 22: return pictureBox23;
			case 23: return pictureBox24;
			case 24: return pictureBox25;
			case 25: return pictureBox26;
			case 26: return pictureBox27;
			case 27: return pictureBox28;
			case 28: return pictureBox29;
			case 29: return pictureBox30;
			case 30: return pictureBox31;
			case 31: return pictureBox32;
			case 32: return pictureBox33;
			case 33: return pictureBox34;
			case 34: return pictureBox35;
			case 35: return pictureBox36;
			case 36: return pictureBox37;
			case 37: return pictureBox38;
			case 38: return pictureBox39;
			case 39: return pictureBox40;
			case 40: return pictureBox41;
			case 41: return pictureBox42;
			}
		}

		// Use to decode a PictureBox handle into an index.
		// Input: the handle of a PictureBox.
		// Output: the corresponding index.
		int PtoN(System::Object^  sender)
		{
			if (ReferenceEquals(sender,pictureBox1)) return 0;
			if (ReferenceEquals(sender,pictureBox2)) return 1;
			if (ReferenceEquals(sender,pictureBox3)) return 2;
			if (ReferenceEquals(sender,pictureBox4)) return 3;
			if (ReferenceEquals(sender,pictureBox5)) return 4;
			if (ReferenceEquals(sender,pictureBox6)) return 5;
			if (ReferenceEquals(sender,pictureBox7)) return 6;
			if (ReferenceEquals(sender,pictureBox8)) return 7;
			if (ReferenceEquals(sender,pictureBox9)) return 8;
			if (ReferenceEquals(sender,pictureBox10)) return 9;
			if (ReferenceEquals(sender,pictureBox11)) return 10;
			if (ReferenceEquals(sender,pictureBox12)) return 11;
			if (ReferenceEquals(sender,pictureBox13)) return 12;
			if (ReferenceEquals(sender,pictureBox14)) return 13;
			if (ReferenceEquals(sender,pictureBox15)) return 14;
			if (ReferenceEquals(sender,pictureBox16)) return 15;
			if (ReferenceEquals(sender,pictureBox17)) return 16;
			if (ReferenceEquals(sender,pictureBox18)) return 17;
			if (ReferenceEquals(sender,pictureBox19)) return 18;
			if (ReferenceEquals(sender,pictureBox20)) return 19;
			if (ReferenceEquals(sender,pictureBox21)) return 20;
			if (ReferenceEquals(sender,pictureBox22)) return 21;
			if (ReferenceEquals(sender,pictureBox23)) return 22;
			if (ReferenceEquals(sender,pictureBox24)) return 23;
			if (ReferenceEquals(sender,pictureBox25)) return 24;
			if (ReferenceEquals(sender,pictureBox26)) return 25;
			if (ReferenceEquals(sender,pictureBox27)) return 26;
			if (ReferenceEquals(sender,pictureBox28)) return 27;
			if (ReferenceEquals(sender,pictureBox29)) return 28;
			if (ReferenceEquals(sender,pictureBox30)) return 29;
			if (ReferenceEquals(sender,pictureBox31)) return 30;
			if (ReferenceEquals(sender,pictureBox32)) return 31;
			if (ReferenceEquals(sender,pictureBox33)) return 32;
			if (ReferenceEquals(sender,pictureBox34)) return 33;
			if (ReferenceEquals(sender,pictureBox35)) return 34;
			if (ReferenceEquals(sender,pictureBox36)) return 35;
			if (ReferenceEquals(sender,pictureBox37)) return 36;
			if (ReferenceEquals(sender,pictureBox38)) return 37;
			if (ReferenceEquals(sender,pictureBox39)) return 38;
			if (ReferenceEquals(sender,pictureBox40)) return 39;
			if (ReferenceEquals(sender,pictureBox41)) return 40;
			if (ReferenceEquals(sender,pictureBox42)) return 41;
		}

		// Response to a click action.
		// Input: the index that which card is clicked.
		void Response(int n)
		{
			if (Game->getAImode()==false)
			{
			if ((timer1->Enabled==true)&&(timer2->Enabled==false)&&(Game->clickable(n)))
			 {
				 // Clear condition.
				pictureBox47->Visible=false;
				pictureBox48->Visible=false;
				 switch (Game->response(n))
				 {
				 case 0:
					 GetState(n);
					 break;
				 case 1:
					 timer2->Interval=300;
					 timer2->Enabled=true;
					 GetState(n);
					 break;
				 case row::FORCE:
					 // For HUNTER.
					 if ((Game->gethero()==gamerules::HUNTER)&&(User->getcredit()>=1))
						 User->setcredit(User->getcredit()-1);
					 User->writefile();
					 label5->Text=""+User->getcredit();
					 RefreshItem(true);

					 timer2->Interval=800;
					 timer2->Enabled=true;
					 Print();
					 break;
				 case row::CHAOS:
					 // For HUNTER.
					 if ((Game->gethero()==gamerules::HUNTER)&&(User->getcredit()>=1))
						 User->setcredit(User->getcredit()-1);
					 User->writefile();
					 label5->Text=""+User->getcredit();
					 RefreshItem(true);

					 timer2->Interval=1200;
					 timer2->Enabled=true;
					 Print();
					 break;
				 case row::CREDIT:
					 // Add credit, write to the user file and refresh to show.
					 User->setcredit(User->getcredit()+3); // Here changes the credit to be added.
					 // For HUNTER.
					 if (Game->gethero()==gamerules::HUNTER)
						 User->setcredit(User->getcredit()+3);
					 User->writefile();
					 label5->Text=""+User->getcredit();
					 RefreshItem(true);

					 timer2->Interval=400;
					 timer2->Enabled=true;
					 GetState(n);
					 break;
				 case row::MATCH:
					 timer2->Interval=500;
					 timer2->Enabled=true;
					 Print();
					 break;
				 case row::TIME:
					 pictureBox51->Invalidate();
					 if (Game->gethero()!=gamerules::MASTER)
					 {
						timer2->Interval=400;
						timer2->Enabled=true;
					 }
					 else
					 {
						timer2->Interval=10;
						timer2->Enabled=true;
					 }
					 GetState(n);
					 break;
				 case row::GIFT:
					 // For HUNTER.
					 if (Game->gethero()==gamerules::HUNTER)
						 User->setcredit(User->getcredit()+1);
					 User->writefile();
					 label5->Text=""+User->getcredit();
					 RefreshItem(true);

					 gift=true;
					 timer2->Interval=400;
					 timer2->Enabled=true;
					 GetState(n);
					 break;
				 }
			 }
			}
			else
			{
				if ((timer3->Enabled==false)&&(GetState(n)==row::COVER))
				{
					// Clear condition.
					pictureBox47->Visible=false;
					pictureBox48->Visible=false;
					switch (Game->response(n))
					{
					case 0:
						GetState(n);
						break;
					case 1:
						timer3->Interval=300;
						timer3->Enabled=true;
						GetState(n);
						break;
					}
				}
			}
		}

		// Refresh the item bar. Edit here and correspoing buttons to change the cost of each item.
		// Input: whether the game is running or not.
		void RefreshItem(bool run)
		{
			// Shop. Enabled when game off.
			pictureBox55->Visible=!run;
			// Set. Enabled when game off.
			pictureBox46->Visible=(!run)&&(User->getcredit()>=5);
			// Reset. Enabled when game off.
			pictureBox54->Visible=(!run);
			// AI. Enabled when game off.
			pictureBox49->Visible=(!run);
		}
		// Print all the cards.
		void Print()
		{
			for (int i=0;i<42;i++) GetState(i);
		}
		
		// Get the state of a single card.
		// Input: the index of the card.
		// Output: (if needed) output the state or kind of the card.
		int GetState(int n)
		{
			int s=Game->getp(n);
			String ^ ImagePath=".\\cards\\0.gif";
			bool V=true;
			switch (s)
			{
			case row::NE: V=false; break;
			default:
				ImagePath=".\\cards\\"+s+".gif";
				break;
			}
			if ((Game->gethero()==gamerules::MASTER)&&(s==row::TIME))
				ImagePath=".\\heroes\\t.png";
			NtoP(n)->Visible=V;
			NtoP(n)->Image=Image::FromFile(ImagePath);
			return s;
		}

		// Start a new game.
		// Input: it is triggered by set operation or not.
		void Start(bool set)
		{
			// Refresh global variables.
			floor=gamerules::NORMAL;
			if (set==false)
				floor=Game->newlevel();
			gift=false;

			pictureBox52->Visible=true;
			pictureBox52->Invalidate();
			pictureBox51->Visible=true;
			pictureBox51->Invalidate();
			pictureBox53->Visible=true;
			pictureBox53->Invalidate();

			RefreshItem(true);
			// Clear the conditions.
			pictureBox47->Visible=false;
			pictureBox48->Visible=false;

			Print();
			// Set buttons.
			pictureBox43->Visible=false; // New Game.
			pictureBox44->Visible=true; // Pause.
			pictureBox45->Visible=false; // Resume.
			pictureBox57->Visible=false; // Next Floor.
			pictureBox56->Enabled=false; // Change hero.
			// Ready for the next level, MUST done in the end.
			String ^ M="";
			String ^ T="";
			label6->Visible=true;
			switch (floor)
			{
			case gamerules::NORMAL:
				label6->Text=""+Game->getlevel();

				M+=""+Game->getkn()+" kinds of attacks, "+Game->getrulen()+" identical attacks to hit.\r\n";
				M+="Start with "+Game->updatenowr()+" rows, "+Game->getpopn()+" rows of reinforcement.\r\n";
				M+="Your helmet will break every "+(Game->gettimeleft()/10)+" seconds.\r\n";
				M+="You need to hit "+Game->gettarget()+" times. Good luck!";
				T+="Floor "+Game->getlevel();

				label15->Visible=true;
				label15->Text=M;
				pictureBox58->Visible=false;
				break;
			case gamerules::CLOWN:
				label6->Text="C";

				M+="A clown Floor, try to survive!";
				T+="CLOWN Floor";
				label15->Visible=false;
				pictureBox58->Visible=true;
				break;
			case gamerules::EVIL:
				label6->Text="E";

				M+="An EVIL Floor, ready to die...";
				T+="EVIL Floor";

				label15->Visible=false;
				pictureBox58->Visible=true;
				break;
			}
			MessageForm ^ MF=gcnew MessageForm(M,T,false,User);
			MF->ShowDialog();
			timer1->Enabled=true;
		}
	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			delete User;
			delete Game;
		}

	protected: 

	private: System::Windows::Forms::Timer^  timer1;

	private: System::ComponentModel::IContainer^  components;

	private:
		userlogin * User;
		gamerules * Game;
		int floor;
		bool gift;


	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: System::Windows::Forms::PictureBox^  pictureBox10;
	private: System::Windows::Forms::PictureBox^  pictureBox11;
	private: System::Windows::Forms::PictureBox^  pictureBox12;
	private: System::Windows::Forms::PictureBox^  pictureBox13;
	private: System::Windows::Forms::PictureBox^  pictureBox14;
	private: System::Windows::Forms::PictureBox^  pictureBox15;
	private: System::Windows::Forms::PictureBox^  pictureBox16;
	private: System::Windows::Forms::PictureBox^  pictureBox17;
	private: System::Windows::Forms::PictureBox^  pictureBox18;
	private: System::Windows::Forms::PictureBox^  pictureBox19;
	private: System::Windows::Forms::PictureBox^  pictureBox20;
	private: System::Windows::Forms::PictureBox^  pictureBox21;
	private: System::Windows::Forms::PictureBox^  pictureBox22;
	private: System::Windows::Forms::PictureBox^  pictureBox23;
	private: System::Windows::Forms::PictureBox^  pictureBox24;
	private: System::Windows::Forms::PictureBox^  pictureBox25;
	private: System::Windows::Forms::PictureBox^  pictureBox26;
	private: System::Windows::Forms::PictureBox^  pictureBox27;
	private: System::Windows::Forms::PictureBox^  pictureBox28;
	private: System::Windows::Forms::PictureBox^  pictureBox29;
	private: System::Windows::Forms::PictureBox^  pictureBox30;
	private: System::Windows::Forms::PictureBox^  pictureBox31;
	private: System::Windows::Forms::PictureBox^  pictureBox32;
	private: System::Windows::Forms::PictureBox^  pictureBox33;
	private: System::Windows::Forms::PictureBox^  pictureBox34;
	private: System::Windows::Forms::PictureBox^  pictureBox35;
	private: System::Windows::Forms::PictureBox^  pictureBox36;
	private: System::Windows::Forms::PictureBox^  pictureBox37;
	private: System::Windows::Forms::PictureBox^  pictureBox38;
	private: System::Windows::Forms::PictureBox^  pictureBox39;
	private: System::Windows::Forms::PictureBox^  pictureBox40;
	private: System::Windows::Forms::PictureBox^  pictureBox41;
	private: System::Windows::Forms::PictureBox^  pictureBox42;




private: System::Windows::Forms::Timer^  timer2;
private: System::Windows::Forms::PictureBox^  pictureBox43;
private: System::Windows::Forms::PictureBox^  pictureBox44;
private: System::Windows::Forms::PictureBox^  pictureBox45;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label2;





private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::PictureBox^  pictureBox50;


private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::PictureBox^  pictureBox46;

private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::PictureBox^  pictureBox47;
private: System::Windows::Forms::PictureBox^  pictureBox48;

private: System::Windows::Forms::PictureBox^  pictureBox49;
private: System::Windows::Forms::Timer^  timer3;


private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::PictureBox^  pictureBox54;

private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::PictureBox^  pictureBox55;

private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::PictureBox^  pictureBox51;
private: System::Windows::Forms::PictureBox^  pictureBox53;
private: System::Windows::Forms::PictureBox^  pictureBox56;
private: System::Windows::Forms::PictureBox^  pictureBox57;
private: System::Windows::Forms::PictureBox^  pictureBox58;
private: System::Windows::Forms::PictureBox^  pictureBox59;


private: System::Windows::Forms::PictureBox^  pictureBox52;





#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox21 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox22 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox24 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox25 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox26 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox27 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox28 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox29 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox30 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox31 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox32 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox33 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox34 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox35 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox36 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox37 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox38 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox39 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox40 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox41 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox42 = (gcnew System::Windows::Forms::PictureBox());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox43 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox44 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox45 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pictureBox50 = (gcnew System::Windows::Forms::PictureBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->pictureBox46 = (gcnew System::Windows::Forms::PictureBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->pictureBox47 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox48 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox49 = (gcnew System::Windows::Forms::PictureBox());
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->pictureBox54 = (gcnew System::Windows::Forms::PictureBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->pictureBox55 = (gcnew System::Windows::Forms::PictureBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->pictureBox51 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox52 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox53 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox56 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox57 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox58 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox59 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox28))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox31))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox32))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox34))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox35))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox36))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox37))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox38))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox39))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox40))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox41))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox42))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox43))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox44))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox45))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox50))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox46))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox47))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox48))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox49))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox54))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox55))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox51))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox52))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox53))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox56))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox57))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox58))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox59))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(26, 535);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(64, 64);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox2->Location = System::Drawing::Point(123, 535);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(64, 64);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Visible = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox3->Location = System::Drawing::Point(219, 535);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(64, 64);
			this->pictureBox3->TabIndex = 5;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Visible = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox4->Location = System::Drawing::Point(315, 535);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(64, 64);
			this->pictureBox4->TabIndex = 6;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Visible = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox5->Location = System::Drawing::Point(412, 535);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(64, 64);
			this->pictureBox5->TabIndex = 7;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Visible = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox6->Location = System::Drawing::Point(508, 535);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(64, 64);
			this->pictureBox6->TabIndex = 8;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Visible = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox7->Location = System::Drawing::Point(605, 535);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(64, 64);
			this->pictureBox7->TabIndex = 9;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Visible = false;
			this->pictureBox7->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox8->Location = System::Drawing::Point(26, 441);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(64, 64);
			this->pictureBox8->TabIndex = 16;
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Visible = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox9->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox9->Location = System::Drawing::Point(123, 441);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(64, 64);
			this->pictureBox9->TabIndex = 15;
			this->pictureBox9->TabStop = false;
			this->pictureBox9->Visible = false;
			this->pictureBox9->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox10
			// 
			this->pictureBox10->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox10->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox10->Location = System::Drawing::Point(219, 441);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(64, 64);
			this->pictureBox10->TabIndex = 14;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->Visible = false;
			this->pictureBox10->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox11
			// 
			this->pictureBox11->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox11->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox11->Location = System::Drawing::Point(315, 441);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(64, 64);
			this->pictureBox11->TabIndex = 13;
			this->pictureBox11->TabStop = false;
			this->pictureBox11->Visible = false;
			this->pictureBox11->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox12
			// 
			this->pictureBox12->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox12->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox12->Location = System::Drawing::Point(412, 441);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(64, 64);
			this->pictureBox12->TabIndex = 12;
			this->pictureBox12->TabStop = false;
			this->pictureBox12->Visible = false;
			this->pictureBox12->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox13
			// 
			this->pictureBox13->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox13->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox13->Location = System::Drawing::Point(508, 441);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(64, 64);
			this->pictureBox13->TabIndex = 11;
			this->pictureBox13->TabStop = false;
			this->pictureBox13->Visible = false;
			this->pictureBox13->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox14
			// 
			this->pictureBox14->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox14->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox14->Location = System::Drawing::Point(605, 441);
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->Size = System::Drawing::Size(64, 64);
			this->pictureBox14->TabIndex = 10;
			this->pictureBox14->TabStop = false;
			this->pictureBox14->Visible = false;
			this->pictureBox14->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox15
			// 
			this->pictureBox15->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox15->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox15->Location = System::Drawing::Point(26, 343);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(64, 64);
			this->pictureBox15->TabIndex = 23;
			this->pictureBox15->TabStop = false;
			this->pictureBox15->Visible = false;
			this->pictureBox15->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox16
			// 
			this->pictureBox16->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox16->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox16->Location = System::Drawing::Point(123, 343);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(64, 64);
			this->pictureBox16->TabIndex = 22;
			this->pictureBox16->TabStop = false;
			this->pictureBox16->Visible = false;
			this->pictureBox16->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox17
			// 
			this->pictureBox17->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox17->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox17->Location = System::Drawing::Point(219, 343);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(64, 64);
			this->pictureBox17->TabIndex = 21;
			this->pictureBox17->TabStop = false;
			this->pictureBox17->Visible = false;
			this->pictureBox17->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox18
			// 
			this->pictureBox18->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox18->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox18->Location = System::Drawing::Point(315, 343);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(64, 64);
			this->pictureBox18->TabIndex = 20;
			this->pictureBox18->TabStop = false;
			this->pictureBox18->Visible = false;
			this->pictureBox18->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox19
			// 
			this->pictureBox19->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox19->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox19->Location = System::Drawing::Point(412, 343);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(64, 64);
			this->pictureBox19->TabIndex = 19;
			this->pictureBox19->TabStop = false;
			this->pictureBox19->Visible = false;
			this->pictureBox19->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox20
			// 
			this->pictureBox20->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox20->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox20->Location = System::Drawing::Point(508, 343);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(64, 64);
			this->pictureBox20->TabIndex = 18;
			this->pictureBox20->TabStop = false;
			this->pictureBox20->Visible = false;
			this->pictureBox20->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox21
			// 
			this->pictureBox21->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox21->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox21->Location = System::Drawing::Point(605, 343);
			this->pictureBox21->Name = L"pictureBox21";
			this->pictureBox21->Size = System::Drawing::Size(64, 64);
			this->pictureBox21->TabIndex = 17;
			this->pictureBox21->TabStop = false;
			this->pictureBox21->Visible = false;
			this->pictureBox21->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox22
			// 
			this->pictureBox22->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox22->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox22->Location = System::Drawing::Point(26, 248);
			this->pictureBox22->Name = L"pictureBox22";
			this->pictureBox22->Size = System::Drawing::Size(64, 64);
			this->pictureBox22->TabIndex = 30;
			this->pictureBox22->TabStop = false;
			this->pictureBox22->Visible = false;
			this->pictureBox22->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox23
			// 
			this->pictureBox23->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox23->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox23->Location = System::Drawing::Point(123, 248);
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->Size = System::Drawing::Size(64, 64);
			this->pictureBox23->TabIndex = 29;
			this->pictureBox23->TabStop = false;
			this->pictureBox23->Visible = false;
			this->pictureBox23->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox24
			// 
			this->pictureBox24->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox24->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox24->Location = System::Drawing::Point(219, 248);
			this->pictureBox24->Name = L"pictureBox24";
			this->pictureBox24->Size = System::Drawing::Size(64, 64);
			this->pictureBox24->TabIndex = 28;
			this->pictureBox24->TabStop = false;
			this->pictureBox24->Visible = false;
			this->pictureBox24->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox25
			// 
			this->pictureBox25->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox25->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox25->Location = System::Drawing::Point(315, 248);
			this->pictureBox25->Name = L"pictureBox25";
			this->pictureBox25->Size = System::Drawing::Size(64, 64);
			this->pictureBox25->TabIndex = 27;
			this->pictureBox25->TabStop = false;
			this->pictureBox25->Visible = false;
			this->pictureBox25->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox26
			// 
			this->pictureBox26->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox26->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox26->Location = System::Drawing::Point(412, 248);
			this->pictureBox26->Name = L"pictureBox26";
			this->pictureBox26->Size = System::Drawing::Size(64, 64);
			this->pictureBox26->TabIndex = 26;
			this->pictureBox26->TabStop = false;
			this->pictureBox26->Visible = false;
			this->pictureBox26->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox27
			// 
			this->pictureBox27->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox27->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox27->Location = System::Drawing::Point(508, 248);
			this->pictureBox27->Name = L"pictureBox27";
			this->pictureBox27->Size = System::Drawing::Size(64, 64);
			this->pictureBox27->TabIndex = 25;
			this->pictureBox27->TabStop = false;
			this->pictureBox27->Visible = false;
			this->pictureBox27->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox28
			// 
			this->pictureBox28->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox28->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox28->Location = System::Drawing::Point(605, 248);
			this->pictureBox28->Name = L"pictureBox28";
			this->pictureBox28->Size = System::Drawing::Size(64, 64);
			this->pictureBox28->TabIndex = 24;
			this->pictureBox28->TabStop = false;
			this->pictureBox28->Visible = false;
			this->pictureBox28->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox29
			// 
			this->pictureBox29->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox29->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox29->Location = System::Drawing::Point(26, 152);
			this->pictureBox29->Name = L"pictureBox29";
			this->pictureBox29->Size = System::Drawing::Size(64, 64);
			this->pictureBox29->TabIndex = 37;
			this->pictureBox29->TabStop = false;
			this->pictureBox29->Visible = false;
			this->pictureBox29->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox30
			// 
			this->pictureBox30->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox30->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox30->Location = System::Drawing::Point(123, 152);
			this->pictureBox30->Name = L"pictureBox30";
			this->pictureBox30->Size = System::Drawing::Size(64, 64);
			this->pictureBox30->TabIndex = 36;
			this->pictureBox30->TabStop = false;
			this->pictureBox30->Visible = false;
			this->pictureBox30->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox31
			// 
			this->pictureBox31->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox31->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox31->Location = System::Drawing::Point(219, 152);
			this->pictureBox31->Name = L"pictureBox31";
			this->pictureBox31->Size = System::Drawing::Size(64, 64);
			this->pictureBox31->TabIndex = 35;
			this->pictureBox31->TabStop = false;
			this->pictureBox31->Visible = false;
			this->pictureBox31->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox32
			// 
			this->pictureBox32->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox32->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox32->Location = System::Drawing::Point(315, 152);
			this->pictureBox32->Name = L"pictureBox32";
			this->pictureBox32->Size = System::Drawing::Size(64, 64);
			this->pictureBox32->TabIndex = 34;
			this->pictureBox32->TabStop = false;
			this->pictureBox32->Visible = false;
			this->pictureBox32->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox33
			// 
			this->pictureBox33->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox33->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox33->Location = System::Drawing::Point(412, 152);
			this->pictureBox33->Name = L"pictureBox33";
			this->pictureBox33->Size = System::Drawing::Size(64, 64);
			this->pictureBox33->TabIndex = 33;
			this->pictureBox33->TabStop = false;
			this->pictureBox33->Visible = false;
			this->pictureBox33->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox34
			// 
			this->pictureBox34->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox34->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox34->Location = System::Drawing::Point(508, 152);
			this->pictureBox34->Name = L"pictureBox34";
			this->pictureBox34->Size = System::Drawing::Size(64, 64);
			this->pictureBox34->TabIndex = 32;
			this->pictureBox34->TabStop = false;
			this->pictureBox34->Visible = false;
			this->pictureBox34->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox35
			// 
			this->pictureBox35->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox35->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox35->Location = System::Drawing::Point(605, 152);
			this->pictureBox35->Name = L"pictureBox35";
			this->pictureBox35->Size = System::Drawing::Size(64, 64);
			this->pictureBox35->TabIndex = 31;
			this->pictureBox35->TabStop = false;
			this->pictureBox35->Visible = false;
			this->pictureBox35->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox36
			// 
			this->pictureBox36->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox36->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox36->Location = System::Drawing::Point(26, 56);
			this->pictureBox36->Name = L"pictureBox36";
			this->pictureBox36->Size = System::Drawing::Size(64, 64);
			this->pictureBox36->TabIndex = 44;
			this->pictureBox36->TabStop = false;
			this->pictureBox36->Visible = false;
			this->pictureBox36->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox37
			// 
			this->pictureBox37->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox37->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox37->Location = System::Drawing::Point(123, 56);
			this->pictureBox37->Name = L"pictureBox37";
			this->pictureBox37->Size = System::Drawing::Size(64, 64);
			this->pictureBox37->TabIndex = 43;
			this->pictureBox37->TabStop = false;
			this->pictureBox37->Visible = false;
			this->pictureBox37->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox38
			// 
			this->pictureBox38->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox38->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox38->Location = System::Drawing::Point(219, 56);
			this->pictureBox38->Name = L"pictureBox38";
			this->pictureBox38->Size = System::Drawing::Size(64, 64);
			this->pictureBox38->TabIndex = 42;
			this->pictureBox38->TabStop = false;
			this->pictureBox38->Visible = false;
			this->pictureBox38->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox39
			// 
			this->pictureBox39->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox39->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox39->Location = System::Drawing::Point(315, 56);
			this->pictureBox39->Name = L"pictureBox39";
			this->pictureBox39->Size = System::Drawing::Size(64, 64);
			this->pictureBox39->TabIndex = 41;
			this->pictureBox39->TabStop = false;
			this->pictureBox39->Visible = false;
			this->pictureBox39->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox40
			// 
			this->pictureBox40->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox40->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox40->Location = System::Drawing::Point(412, 56);
			this->pictureBox40->Name = L"pictureBox40";
			this->pictureBox40->Size = System::Drawing::Size(64, 64);
			this->pictureBox40->TabIndex = 40;
			this->pictureBox40->TabStop = false;
			this->pictureBox40->Visible = false;
			this->pictureBox40->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox41
			// 
			this->pictureBox41->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox41->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox41->Location = System::Drawing::Point(508, 56);
			this->pictureBox41->Name = L"pictureBox41";
			this->pictureBox41->Size = System::Drawing::Size(64, 64);
			this->pictureBox41->TabIndex = 39;
			this->pictureBox41->TabStop = false;
			this->pictureBox41->Visible = false;
			this->pictureBox41->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// pictureBox42
			// 
			this->pictureBox42->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox42->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox42->Location = System::Drawing::Point(605, 56);
			this->pictureBox42->Name = L"pictureBox42";
			this->pictureBox42->Size = System::Drawing::Size(64, 64);
			this->pictureBox42->TabIndex = 38;
			this->pictureBox42->TabStop = false;
			this->pictureBox42->Visible = false;
			this->pictureBox42->Click += gcnew System::EventHandler(this, &Form1::pictureBox_Click);
			// 
			// timer2
			// 
			this->timer2->Interval = 400;
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// pictureBox43
			// 
			this->pictureBox43->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox43->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox43.BackgroundImage")));
			this->pictureBox43->Location = System::Drawing::Point(40, 614);
			this->pictureBox43->Name = L"pictureBox43";
			this->pictureBox43->Size = System::Drawing::Size(91, 90);
			this->pictureBox43->TabIndex = 49;
			this->pictureBox43->TabStop = false;
			this->pictureBox43->Click += gcnew System::EventHandler(this, &Form1::pictureBox43_Click);
			// 
			// pictureBox44
			// 
			this->pictureBox44->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox44->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox44.BackgroundImage")));
			this->pictureBox44->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox44->Location = System::Drawing::Point(153, 614);
			this->pictureBox44->Name = L"pictureBox44";
			this->pictureBox44->Size = System::Drawing::Size(91, 90);
			this->pictureBox44->TabIndex = 50;
			this->pictureBox44->TabStop = false;
			this->pictureBox44->Visible = false;
			this->pictureBox44->Click += gcnew System::EventHandler(this, &Form1::pictureBox44_Click);
			// 
			// pictureBox45
			// 
			this->pictureBox45->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox45->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox45.BackgroundImage")));
			this->pictureBox45->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox45->Location = System::Drawing::Point(266, 614);
			this->pictureBox45->Name = L"pictureBox45";
			this->pictureBox45->Size = System::Drawing::Size(91, 90);
			this->pictureBox45->TabIndex = 51;
			this->pictureBox45->TabStop = false;
			this->pictureBox45->Visible = false;
			this->pictureBox45->Click += gcnew System::EventHandler(this, &Form1::pictureBox45_Click);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(711, 2);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(284, 46);
			this->label1->TabIndex = 52;
			this->label1->Text = L"Username";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Location = System::Drawing::Point(927, 168);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(18, 19);
			this->label2->TabIndex = 53;
			this->label2->Text = L"0";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(817, 234);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(18, 19);
			this->label5->TabIndex = 60;
			this->label5->Text = L"0";
			// 
			// pictureBox50
			// 
			this->pictureBox50->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox50->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox50.BackgroundImage")));
			this->pictureBox50->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox50->Location = System::Drawing::Point(846, 652);
			this->pictureBox50->Name = L"pictureBox50";
			this->pictureBox50->Size = System::Drawing::Size(184, 73);
			this->pictureBox50->TabIndex = 61;
			this->pictureBox50->TabStop = false;
			this->pictureBox50->Click += gcnew System::EventHandler(this, &Form1::pictureBox50_Click);
			// 
			// label6
			// 
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(463, 5);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(46, 47);
			this->label6->TabIndex = 64;
			this->label6->Text = L"000";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label6->Visible = false;
			// 
			// pictureBox46
			// 
			this->pictureBox46->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox46->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox46->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox46.Image")));
			this->pictureBox46->Location = System::Drawing::Point(772, 272);
			this->pictureBox46->Name = L"pictureBox46";
			this->pictureBox46->Size = System::Drawing::Size(48, 56);
			this->pictureBox46->TabIndex = 65;
			this->pictureBox46->TabStop = false;
			this->pictureBox46->Click += gcnew System::EventHandler(this, &Form1::pictureBox46_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label8->ForeColor = System::Drawing::Color::Black;
			this->label8->Location = System::Drawing::Point(1063, 294);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(23, 17);
			this->label8->TabIndex = 67;
			this->label8->Text = L"5C";
			// 
			// pictureBox47
			// 
			this->pictureBox47->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox47->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox47->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox47.Image")));
			this->pictureBox47->Location = System::Drawing::Point(351, 5);
			this->pictureBox47->Name = L"pictureBox47";
			this->pictureBox47->Size = System::Drawing::Size(66, 29);
			this->pictureBox47->TabIndex = 68;
			this->pictureBox47->TabStop = false;
			this->pictureBox47->Visible = false;
			// 
			// pictureBox48
			// 
			this->pictureBox48->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox48->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox48.BackgroundImage")));
			this->pictureBox48->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox48->Location = System::Drawing::Point(960, 222);
			this->pictureBox48->Name = L"pictureBox48";
			this->pictureBox48->Size = System::Drawing::Size(59, 46);
			this->pictureBox48->TabIndex = 69;
			this->pictureBox48->TabStop = false;
			this->pictureBox48->Visible = false;
			// 
			// pictureBox49
			// 
			this->pictureBox49->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox49->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox49->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox49.Image")));
			this->pictureBox49->Location = System::Drawing::Point(761, 410);
			this->pictureBox49->Name = L"pictureBox49";
			this->pictureBox49->Size = System::Drawing::Size(62, 54);
			this->pictureBox49->TabIndex = 71;
			this->pictureBox49->TabStop = false;
			this->pictureBox49->Click += gcnew System::EventHandler(this, &Form1::pictureBox49_Click);
			// 
			// timer3
			// 
			this->timer3->Tick += gcnew System::EventHandler(this, &Form1::timer3_Tick);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label10->ForeColor = System::Drawing::Color::Black;
			this->label10->Location = System::Drawing::Point(1055, 428);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(41, 17);
			this->label10->TabIndex = 74;
			this->label10->Text = L"FREE!";
			// 
			// pictureBox54
			// 
			this->pictureBox54->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox54->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox54->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox54.Image")));
			this->pictureBox54->Location = System::Drawing::Point(772, 343);
			this->pictureBox54->Name = L"pictureBox54";
			this->pictureBox54->Size = System::Drawing::Size(49, 52);
			this->pictureBox54->TabIndex = 75;
			this->pictureBox54->TabStop = false;
			this->pictureBox54->Click += gcnew System::EventHandler(this, &Form1::pictureBox54_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label12->ForeColor = System::Drawing::Color::Black;
			this->label12->Location = System::Drawing::Point(1055, 357);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(41, 17);
			this->label12->TabIndex = 77;
			this->label12->Text = L"FREE!";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label13->ForeColor = System::Drawing::Color::Black;
			this->label13->Location = System::Drawing::Point(893, 193);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(18, 19);
			this->label13->TabIndex = 78;
			this->label13->Text = L"0";
			// 
			// pictureBox55
			// 
			this->pictureBox55->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox55->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox55.BackgroundImage")));
			this->pictureBox55->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox55->Location = System::Drawing::Point(1027, 212);
			this->pictureBox55->Name = L"pictureBox55";
			this->pictureBox55->Size = System::Drawing::Size(83, 63);
			this->pictureBox55->TabIndex = 79;
			this->pictureBox55->TabStop = false;
			this->pictureBox55->Click += gcnew System::EventHandler(this, &Form1::pictureBox55_Click);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::Transparent;
			this->label15->Font = (gcnew System::Drawing::Font(L"Î¢ÈíÑÅºÚ", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label15->Location = System::Drawing::Point(746, 528);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(178, 19);
			this->label15->TabIndex = 81;
			this->label15->Text = L"Come on to a new floor!";
			// 
			// pictureBox51
			// 
			this->pictureBox51->BackColor = System::Drawing::Color::Black;
			this->pictureBox51->Location = System::Drawing::Point(376, 627);
			this->pictureBox51->Name = L"pictureBox51";
			this->pictureBox51->Size = System::Drawing::Size(121, 19);
			this->pictureBox51->TabIndex = 82;
			this->pictureBox51->TabStop = false;
			this->pictureBox51->Visible = false;
			this->pictureBox51->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox51_Paint);
			// 
			// pictureBox52
			// 
			this->pictureBox52->BackColor = System::Drawing::Color::Black;
			this->pictureBox52->Location = System::Drawing::Point(57, 12);
			this->pictureBox52->Name = L"pictureBox52";
			this->pictureBox52->Size = System::Drawing::Size(285, 19);
			this->pictureBox52->TabIndex = 83;
			this->pictureBox52->TabStop = false;
			this->pictureBox52->Visible = false;
			this->pictureBox52->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox52_Paint);
			// 
			// pictureBox53
			// 
			this->pictureBox53->BackColor = System::Drawing::Color::Black;
			this->pictureBox53->Location = System::Drawing::Point(376, 681);
			this->pictureBox53->Name = L"pictureBox53";
			this->pictureBox53->Size = System::Drawing::Size(121, 19);
			this->pictureBox53->TabIndex = 84;
			this->pictureBox53->TabStop = false;
			this->pictureBox53->Visible = false;
			this->pictureBox53->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox53_Paint);
			// 
			// pictureBox56
			// 
			this->pictureBox56->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox56->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox56.Image")));
			this->pictureBox56->Location = System::Drawing::Point(567, 611);
			this->pictureBox56->Name = L"pictureBox56";
			this->pictureBox56->Size = System::Drawing::Size(88, 109);
			this->pictureBox56->TabIndex = 85;
			this->pictureBox56->TabStop = false;
			this->pictureBox56->Click += gcnew System::EventHandler(this, &Form1::pictureBox56_Click);
			// 
			// pictureBox57
			// 
			this->pictureBox57->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox57->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox57->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox57.Image")));
			this->pictureBox57->Location = System::Drawing::Point(298, 233);
			this->pictureBox57->Name = L"pictureBox57";
			this->pictureBox57->Size = System::Drawing::Size(99, 99);
			this->pictureBox57->TabIndex = 86;
			this->pictureBox57->TabStop = false;
			this->pictureBox57->Visible = false;
			this->pictureBox57->Click += gcnew System::EventHandler(this, &Form1::pictureBox57_Click);
			// 
			// pictureBox58
			// 
			this->pictureBox58->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox58->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox58->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox58.Image")));
			this->pictureBox58->Location = System::Drawing::Point(789, 479);
			this->pictureBox58->Name = L"pictureBox58";
			this->pictureBox58->Size = System::Drawing::Size(298, 155);
			this->pictureBox58->TabIndex = 87;
			this->pictureBox58->TabStop = false;
			this->pictureBox58->Visible = false;
			// 
			// pictureBox59
			// 
			this->pictureBox59->BackColor = System::Drawing::Color::Black;
			this->pictureBox59->Location = System::Drawing::Point(963, 143);
			this->pictureBox59->Name = L"pictureBox59";
			this->pictureBox59->Size = System::Drawing::Size(141, 19);
			this->pictureBox59->TabIndex = 88;
			this->pictureBox59->TabStop = false;
			this->pictureBox59->Click += gcnew System::EventHandler(this, &Form1::pictureBox59_Click);
			this->pictureBox59->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox59_Paint);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1180, 728);
			this->Controls->Add(this->pictureBox59);
			this->Controls->Add(this->pictureBox58);
			this->Controls->Add(this->pictureBox57);
			this->Controls->Add(this->pictureBox56);
			this->Controls->Add(this->pictureBox53);
			this->Controls->Add(this->pictureBox52);
			this->Controls->Add(this->pictureBox51);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->pictureBox55);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->pictureBox54);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->pictureBox49);
			this->Controls->Add(this->pictureBox48);
			this->Controls->Add(this->pictureBox47);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->pictureBox46);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->pictureBox50);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox45);
			this->Controls->Add(this->pictureBox44);
			this->Controls->Add(this->pictureBox43);
			this->Controls->Add(this->pictureBox36);
			this->Controls->Add(this->pictureBox37);
			this->Controls->Add(this->pictureBox38);
			this->Controls->Add(this->pictureBox39);
			this->Controls->Add(this->pictureBox40);
			this->Controls->Add(this->pictureBox41);
			this->Controls->Add(this->pictureBox42);
			this->Controls->Add(this->pictureBox29);
			this->Controls->Add(this->pictureBox30);
			this->Controls->Add(this->pictureBox31);
			this->Controls->Add(this->pictureBox32);
			this->Controls->Add(this->pictureBox33);
			this->Controls->Add(this->pictureBox34);
			this->Controls->Add(this->pictureBox35);
			this->Controls->Add(this->pictureBox22);
			this->Controls->Add(this->pictureBox23);
			this->Controls->Add(this->pictureBox24);
			this->Controls->Add(this->pictureBox25);
			this->Controls->Add(this->pictureBox26);
			this->Controls->Add(this->pictureBox27);
			this->Controls->Add(this->pictureBox28);
			this->Controls->Add(this->pictureBox15);
			this->Controls->Add(this->pictureBox16);
			this->Controls->Add(this->pictureBox17);
			this->Controls->Add(this->pictureBox18);
			this->Controls->Add(this->pictureBox19);
			this->Controls->Add(this->pictureBox20);
			this->Controls->Add(this->pictureBox21);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox9);
			this->Controls->Add(this->pictureBox10);
			this->Controls->Add(this->pictureBox11);
			this->Controls->Add(this->pictureBox12);
			this->Controls->Add(this->pictureBox13);
			this->Controls->Add(this->pictureBox14);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MemoryGame47";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox28))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox31))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox32))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox34))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox35))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox36))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox37))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox38))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox39))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox40))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox41))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox42))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox43))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox44))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox45))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox50))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox46))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox47))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox48))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox49))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox54))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox55))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox51))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox52))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox53))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox56))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox57))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox58))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox59))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
// This is the New Game button.
private: System::Void pictureBox43_Click(System::Object^  sender, System::EventArgs^  e) {
			// Reset the current level and open a new level.
			Game->setlevel(User->getsave());
			Start(false);
		 }
// This is the Pause button.
private: System::Void pictureBox44_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (timer2->Enabled==false)
			 {
				timer1->Enabled=false;
				pictureBox43->Visible=true;
				pictureBox44->Visible=false;
				pictureBox45->Visible=true;
				pictureBox47->Visible=false;
				pictureBox48->Visible=false;
				RefreshItem(false);
			 }
		 }
// This is the Resume button.
private: System::Void pictureBox45_Click(System::Object^  sender, System::EventArgs^  e) {
			 pictureBox43->Visible=false;
			 pictureBox44->Visible=true;
			 pictureBox45->Visible=false;
			 RefreshItem(true);
			 timer1->Enabled=true;
		 }
// This is the Exit button.
private: System::Void pictureBox50_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
// This is the normal game timing timer.
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				if (Game->gettimeleft()>0)
				{
					Game->settimeleft(Game->gettimeleft()-1);
					pictureBox51->Invalidate();
				}
				else
				{
					if (timer2->Enabled==false)
					{
						bool check=Game->poprow(Game->getpopn());
						if (check==true) // Pop a new row and reset the progressBar1.
						{
							pictureBox52->Invalidate();
							pictureBox53->Invalidate();
							Print();
							pictureBox47->Visible=false;
							pictureBox48->Visible=false;
							pictureBox51->Invalidate();
						}
						else // Game over.
						{
							// Stop timing.
							timer1->Enabled=false;
							timer2->Enabled=false;
							// Set score and time to zero, re-print all.
							label6->Text="0";
							pictureBox52->Visible=false;
							pictureBox51->Visible=false;
							pictureBox53->Visible=false;
							// Clear the condition.
							pictureBox47->Visible=false;
							pictureBox48->Visible=false;

							RefreshItem(false);
							Print();
							// Set the buttons.
							pictureBox43->Visible=true;
							pictureBox44->Visible=false;
							pictureBox45->Visible=false;
							pictureBox56->Enabled=true; // Change hero.
							// Show Game over message.
							String ^ M="Time's Up!\r\n";
							M+="Game over.";
							label15->Text=M;
							MessageForm ^ MF=gcnew MessageForm(M,"Game Over",false,User);
							MF->ShowDialog();
						}
					}
				}
		 }
// This is the closing timer.
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 timer2->Enabled=false; // The timer will disable until next activation.
			 // Do closing, get score, and re-print all.
			 bool flag;
			 int cond;
			 Game->closing(&flag,&cond);
			 pictureBox53->Visible=true;
			 pictureBox53->Invalidate();
			 // Refresch condition.
			 switch (cond)
			 {
			 case gamerules::SCORE:
				 pictureBox47->Image=Image::FromFile(".\\UI\\score.png");
				 pictureBox47->Visible=true;
				 break;
			 case gamerules::BONUS:
				 pictureBox47->Image=Image::FromFile(".\\UI\\bonus.png");
				 pictureBox47->Visible=true;
				 break;
			 case gamerules::CREDIT:
				 pictureBox47->Image=Image::FromFile(".\\UI\\bonus.png");
				 pictureBox47->Visible=true;
				 pictureBox48->Visible=true;
				 break;
			 case gamerules::COMBO:
				 pictureBox47->Image=Image::FromFile(".\\UI\\combo.png");
				 pictureBox47->Visible=true;
				 break;
			 case gamerules::BREAK:
				 pictureBox47->Image=Image::FromFile(".\\UI\\break.png");
				 pictureBox47->Visible=true;
				 break;
			 case gamerules::CRITICAL:
				 pictureBox47->Image=Image::FromFile(".\\UI\\critical.png");
				 pictureBox47->Visible=true;
				 break;
			 }
			 pictureBox52->Invalidate();
			 Print();
			 if (flag) // If go to the next level.
			 {
				// Stop timing.
				timer1->Enabled=false;
				// Rewards to the game.
				if (gift)
				{
					String ^ M="You find a gift in this floor!\r\n";
					M+="Please receive it!";
					MessageForm ^ MF=gcnew MessageForm(M,"Wow",true,User);
					MF->ShowDialog();
				}
				switch (floor)
				{
				case gamerules::NORMAL:
					User->setcredit(User->getcredit()+1);
					break;
				case gamerules::CLOWN:
					User->setcredit(User->getcredit()+3);
					break;
				case gamerules::EVIL:
					User->setcredit(User->getcredit()+5);
					String ^ M="You get the Chest of EVIL!\r\n";
					M+="Let's open it!";
					MessageForm ^ MF=gcnew MessageForm(M,"Wow",true,User);
					MF->ShowDialog();
					break;
				}
				User->writefile();
				label5->Text=""+User->getcredit();
				pictureBox59->Invalidate();
				// Re-print all.
				pictureBox51->Visible=false;
				pictureBox53->Visible=false;

				RefreshItem(false);
			    // Clear the conditions.
			    pictureBox47->Visible=false;
			    pictureBox48->Visible=false;

			    Print();
				// Set the buttons.
				pictureBox44->Visible=false;
				pictureBox45->Visible=false;
				pictureBox56->Enabled=true; // Change hero.
			    // Write to user file.
			    User->setsave(Game->getlevel());
			    label13->Text=""+Game->getlevel();
				if (Game->getlevel()>User->getlevel())
				{
					User->setlevel(Game->getlevel());
					label2->Text=""+Game->getlevel();
				}
				User->writefile();
				// Show the button to the next floor.
				String ^ M="Well done!\r\n";
				M+="Let's go to the next floor!";
				label15->Text=M;
				pictureBox57->Visible=true; 
			 }
		 }
// This is the AI closing timer.
private: System::Void timer3_Tick(System::Object^  sender, System::EventArgs^  e) {
			 timer3->Enabled=false; // The timer will disable until next activation.
			 bool flag=false;
			 int cond;
			 if (Game->getAI()==false)
			 {
				Game->AIclosing(&flag,&cond);
				 // Refresch condition.
				if (cond==gamerules::SCORE)
				{
					pictureBox52->Invalidate();
					pictureBox47->Image=Image::FromFile(".\\UI\\score.png");
					pictureBox47->Visible=true;
				}
				Print();
				if (Game->getAI()==true)
				{
					// Change to the AI's turn.
					label6->Text="M";
					pictureBox43->Visible=false;
					RefreshItem(true);
					timer3->Interval=1000;
					timer3->Enabled=true;
				}
			 }
			 else
			 {
				 switch (Game->AIclick())
				 {
				 case 1:
					 Game->AIclosing(&flag,&cond);
					 if (cond==gamerules::AISCORE)
					 {
						pictureBox52->Invalidate();
						pictureBox47->Image=Image::FromFile(".\\UI\\break.png");
						pictureBox47->Visible=true;
					 }
					 if (Game->getAI()==false)
					 {
						 // Change to player's turn.
						 label6->Text="U";
						 pictureBox43->Visible=true; // New Game.
						 RefreshItem(false);
					 }
					 break;
				 case 2:
					 timer3->Interval=1000;
					 timer3->Enabled=true;
					 break;
				 case 3:
					 timer3->Interval=1000;
					 timer3->Enabled=true;
					 break;
				 }
				 Print();
				 if (Game->getAI()==true)
				 {
					// Maintain in AI's turn.
					timer3->Interval=1000;
					timer3->Enabled=true;
				 }
			 }
			 if (flag)
			 {
				 timer3->Enabled=false;
				 String ^ M="";
				 if (Game->getscore()==Game->getAIscore())
				 {
					 M+="You get the same score as your master.\r\n";
					 M+="Please start another training!";
					 label15->Text=M;
					 MessageForm ^ MF=gcnew MessageForm(M,"Draw",false,User);
					 MF->ShowDialog();
				 }
				 if (Game->getscore()>Game->getAIscore())
				 {
					 // First give player extra credits.
					 int wincredit=(Game->getscore()-Game->getAIscore())/4+1;
					 User->setcredit(User->getcredit()+wincredit);
					 // Adjust the AI remember percentage.
					 int adjust=Game->getscore()-Game->getAIscore(); // A positive number.
					 if (User->getAIrp()+adjust<=100)
						 User->setAIrp(User->getAIrp()+adjust);
					 else
						 User->setAIrp(100);
					 User->writefile();
					 label5->Text=""+User->getcredit();
					 M+="Congratulations! You win your master!\r\n";
					 M+="You have earn "+wincredit+" credits!\r\n";
					 M+="Please start a new training to win more!";
					 label15->Text=M;
					 MessageForm ^ MF=gcnew MessageForm(M,"Win",false,User);
					 MF->ShowDialog();
				 }
				 if (Game->getscore()<Game->getAIscore())
				 {
					 // Adjust the AI remember percentage.
					 int adjust=Game->getscore()-Game->getAIscore(); // A negative number.
					 if (User->getAIrp()+adjust>=0)
						 User->setAIrp(User->getAIrp()+adjust);
					 else
						 User->setAIrp(0);
					 User->writefile();
					 M+="It's a pity that you lose this time.\r\n";
					 M+="Please start a new training and try again!";
					 label15->Text=M;
					 MessageForm ^ MF=gcnew MessageForm(M,"Lose",false,User);
					 MF->ShowDialog();
				 }
				 // Set score and time to zero, re-print all.
				 pictureBox52->Invalidate();
				 // Clear the condition.
				 pictureBox47->Visible=false;
				 pictureBox48->Visible=false;
				 RefreshItem(false);
				 Print();
				 // Set the buttons.
				 pictureBox43->Visible=true;
				 pictureBox56->Enabled=true; // Change hero.
			 }
		 }
// Open Shop Form.
private: System::Void pictureBox55_Click(System::Object^  sender, System::EventArgs^  e) {
			 ShopForm ^ SF=gcnew ShopForm(User);
			 SF->ShowDialog();
			 RefreshItem(false);
			 label5->Text=""+User->getcredit();
			 pictureBox59->Invalidate();
		 }
// Item - Set.
private: System::Void pictureBox46_Click(System::Object^  sender, System::EventArgs^  e) {
			 // Minus credit, write to the user file and refresh to show.
			 User->setcredit(User->getcredit()-5); // Edit here to change the cost of it.
			 User->writefile();
			 label5->Text=""+User->getcredit();
			 RefreshItem(false);
			 // Show the message.
			 String ^ M="You pay 5 credits to buy the items.\r\n"; // Edit here to change the cost of it.
			 M+="Ready to choose the next floor!";
			 MessageForm ^ MF=gcnew MessageForm(M,"Jumping",false,User);
			 MF->ShowDialog();
			 // Show the set form.
			 SetForm ^ SF=gcnew SetForm(Game,User);
			 SF->ShowDialog(); // The setting of starting a new game is set in the SetForm object.
			 // Acts like a new game.
			 Start(true);
		 }
// Item - Reset.
private: System::Void pictureBox54_Click(System::Object^  sender, System::EventArgs^  e) {
			
			int wincredit=Game->getlevel()/3;
			User->setcredit(User->getcredit()+wincredit);
			Game->setlevel(0);
			User->setsave(0);
			User->writefile();
			label5->Text=""+User->getcredit();
			label13->Text="0";
			// Acts like Game over.
			// Stop timing.
			timer1->Enabled=false;
			timer2->Enabled=false;
			// Clear the condition.
			pictureBox47->Visible=false;
			pictureBox48->Visible=false;
			RefreshItem(false);
			// Set the buttons.
			pictureBox43->Visible=true;
			pictureBox44->Visible=false;
			pictureBox45->Visible=false;
			pictureBox57->Visible=false;
			pictureBox56->Enabled=true; // Change hero.
		    // Show message.
			String ^ M="Welcome back to your hometown!\r\n";
			M+="And your conquests earn "+ wincredit+ " credits.\r\n";
			M+="Ready to fight again!";
			MessageForm ^ MF=gcnew MessageForm(M,"Welcome back",false,User);
		    MF->ShowDialog();
		 }
// Item - AI.
private: System::Void pictureBox49_Click(System::Object^  sender, System::EventArgs^  e) {
			 // Set the level the saved one and open a new level.
			Game->AIlevel(100-User->getAIrp()); // Notice that the user file records remember percentage, here is forget percentage.
			label6->Text="U";
			label6->Visible=true;
			// Reset the score and time and reprint all.
			pictureBox52->Visible=true;
			pictureBox52->Invalidate();
			pictureBox51->Visible=false;
			pictureBox53->Visible=false;

			RefreshItem(false);
			Print();
			// Set buttons.
			pictureBox43->Visible=true; // New Game.
			pictureBox44->Visible=false; // Pause.
			pictureBox45->Visible=false; // Resume.
			pictureBox57->Visible=false; // Next Floor.
			pictureBox56->Enabled=true; // Change hero.
			// Ready for the new game, MUST done in the end.
			String ^ M="Ready to fight your master!\r\n";
			M+="The forget percentage of your master is "+ (100-User->getAIrp())+ "%!";
			label15->Visible=true;
			label15->Text=M;
			pictureBox58->Visible=false;
			MessageForm ^ MF=gcnew MessageForm(M,"Hello Master",false,User);
			MF->ShowDialog();
		 }
// The following are the event handlers when the 42 PictureBoxes are clicked.
private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
			 Response(PtoN(sender));
		 }
// Show the helmet of the user.
private: System::Void pictureBox51_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 Graphics ^g = e->Graphics;
			 Drawing::Rectangle Time = Drawing::Rectangle(0, 0, pictureBox51->Size.Width*Game->gettimeleft()/Game->getbasetime(), pictureBox51->Size.Height);
			 g->FillRectangle(Brushes::Blue, Time);
			 Pen ^P = gcnew Pen(Color::Black, 4);
			 g->DrawRectangle(P, Time);
		 }
// Show the process of the user.
private: System::Void pictureBox52_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 Graphics ^g = e->Graphics;
			 Pen ^P = gcnew Pen(Color::Black, 4);
			 if (Game->getAImode()==false)
			 {
				Drawing::Rectangle Wave;
				if (floor==gamerules::NORMAL)
				{
					Wave = Drawing::Rectangle(pictureBox52->Size.Width-pictureBox52->Size.Width*Game->getscore()/Game->gettarget(),0, pictureBox52->Size.Width*Game->getscore()/Game->gettarget(), pictureBox52->Size.Height);
					g->FillRectangle(Brushes::Yellow, Wave);
					g->DrawRectangle(P, Wave);
				}
				else
				{
					Wave = Drawing::Rectangle(0,0, pictureBox52->Size.Width-pictureBox52->Size.Width*Game->getscore()/Game->gettarget(), pictureBox52->Size.Height);
					g->FillRectangle(Brushes::Orchid, Wave);
					g->DrawRectangle(P, Wave);
				}
			 }
			 else
			 {
				 int ratio=0;
				 if ((Game->getscore()+Game->getAIscore())==0)
					 ratio=pictureBox52->Size.Width/2;
				 else
					 ratio=pictureBox52->Size.Width*Game->getAIscore()/(Game->getscore()+Game->getAIscore());
				Drawing::Rectangle AIS = Drawing::Rectangle(0,0,ratio, pictureBox52->Size.Height);
				g->FillRectangle(Brushes::Red, AIS);
				g->DrawRectangle(P, AIS);
				Drawing::Rectangle PS = Drawing::Rectangle(ratio,0,pictureBox52->Size.Width-ratio, pictureBox52->Size.Height);
				g->FillRectangle(Brushes::Yellow, PS);
				g->DrawRectangle(P, PS);
			 }
		 }
// Show the life of the user.
private: System::Void pictureBox53_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 Graphics ^g = e->Graphics;
			 if (Game->updatenowr()+Game->getpopn()>maxr)
			 {
				 pictureBox56->Image=Image::FromFile(".\\heroes\\"+Game->gethero()+"_d.png");
			 }
			 else
			 {
				Drawing::Rectangle Life = Drawing::Rectangle(0, 0, pictureBox53->Size.Width-pictureBox53->Size.Width*(Game->updatenowr()-1)/maxr, pictureBox53->Size.Height);
				g->FillRectangle(Brushes::Red, Life);
				Pen ^P = gcnew Pen(Color::Black, 4);
				g->DrawRectangle(P, Life);
				pictureBox56->Image=Image::FromFile(".\\heroes\\"+Game->gethero()+".png");
			 }
		 }
// Use to go to the next floor.
private: System::Void pictureBox57_Click(System::Object^  sender, System::EventArgs^  e) {
			 // Set a new level, reset the score and time and re-print all.
			 Start(false);
		 }
// Show the collation rate of the user.
private: System::Void pictureBox59_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 Graphics ^g = e->Graphics;
			 Drawing::Rectangle Rate = Drawing::Rectangle(0, 0, pictureBox59->Size.Width*User->getrate()/100, pictureBox59->Size.Height);
			 g->FillRectangle(Brushes::LightGreen, Rate);
			 Pen ^P = gcnew Pen(Color::Black, 4);
			 g->DrawRectangle(P, Rate);
		 }
// Open the achievenment form.
private: System::Void pictureBox59_Click(System::Object^  sender, System::EventArgs^  e) {
			 FinderForm ^ FF=gcnew FinderForm(User,maxk,maxsp,offset);
			 FF->ShowDialog();
		 }
// Open the hero form.
private: System::Void pictureBox56_Click(System::Object^  sender, System::EventArgs^  e) {
			 HeroForm ^ HF=gcnew HeroForm(User);
			 HF->ShowDialog();
			 Game->sethero(User->gethero());
			 pictureBox56->Image=Image::FromFile(".\\heroes\\"+Game->gethero()+".png");
		 }
};
}