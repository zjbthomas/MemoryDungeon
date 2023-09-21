#pragma once
#include "userlogin.h"
namespace MemoryGame47 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MessageForm 摘要
	/// </summary>
	public ref class MessageForm : public System::Windows::Forms::Form
	{
	public:
		MessageForm(String ^ M, String ^ T, bool D, userlogin * U)
		{
			InitializeComponent();
			this->SetStyle(static_cast<ControlStyles>(ControlStyles::AllPaintingInWmPaint |ControlStyles::DoubleBuffer |ControlStyles::UserPaint), true);
			this->UpdateStyles();
			label1->Text=T;
			label2->Text=M;
			draw=D;
			User=U;
			pictureBox1->Enabled=!draw;
			pictureBox2->Enabled=draw;
			pictureBox2->Invalidate();
			x=0;
			cycle=1;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MessageForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox2;

	protected: 

	private:
		userlogin * User;
		bool draw;
		int x,cycle;
		bool result;
		String ^ ImagePath;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MessageForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(55, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(333, 42);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Title";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(202, 303);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(135, 78);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MessageForm::pictureBox1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(51, 161);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 19);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Message";
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->Location = System::Drawing::Point(443, 14);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(80, 80);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MessageForm::pictureBox2_Click);
			this->pictureBox2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MessageForm::pictureBox2_Paint);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MessageForm::timer1_Tick);
			// 
			// MessageForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(539, 393);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MessageForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MessageForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
				this->Close();

			 }
private: System::Void pictureBox2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				Bitmap ^ Bp;	
			    if (draw==true)
					Bp=gcnew Bitmap(".\\cards\\p.png");
				else
					Bp=gcnew Bitmap(".\\UI\\icon_m.png");
				int w=pictureBox2->Size.Width;
				int h=pictureBox2->Size.Height;
				if (timer1->Enabled==false)
				{
					Drawing::Rectangle Area=Drawing::Rectangle(x,0,w-2*x,h);
					e->Graphics->DrawImage(Bp,Area);
					return;
				}
				 if (x<w/2)
				 {
					Drawing::Rectangle Area=Drawing::Rectangle(x,0,w-2*x,h);
					e->Graphics->DrawImage(Bp,Area);
					x+=20;
				 }
				 else if (x<w)
				 {
					 if (cycle==7)
					 {
						Bp=gcnew Bitmap(ImagePath);
						Drawing::Rectangle Area=Drawing::Rectangle(w-x,0,w-2*(w-x),h);
						e->Graphics->DrawImage(Bp,Area);
						x+=20;
					 }
					 else
					 {
						 Drawing::Rectangle Area=Drawing::Rectangle(w-x,0,w-2*(w-x),h);
						 e->Graphics->DrawImage(Bp,Area);
						 x+=20;
					 }
			     }
				 else
				 {
					 if (cycle==7)
					 {
						Bp=gcnew Bitmap(ImagePath);
						Drawing::Rectangle Area=Drawing::Rectangle(0,0,w,h);
						e->Graphics->DrawImage(Bp,Area);
						timer1->Enabled=false;
						if (result==true)
						{
							label2->Text="You find part of your memory!";
						}
						else
						{
							label2->Text="Sorry, not lucky enough.\r\n";
						}
						pictureBox1->Enabled=true;
					 }
					 else
					 {
						Drawing::Rectangle Area=Drawing::Rectangle(0,0,w,h);
						e->Graphics->DrawImage(Bp,Area);
						cycle++;
						x=0;
						timer1->Interval+=10;
					 }
				 }
		 }
private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (timer1->Enabled==false)
			 {
				pictureBox2->Enabled=false;
				x=0;
				cycle=1;
				// Dealing with purchase action.
				int pass=0;
				result=User->randompk(&pass);
				ImagePath=".\\cards\\"+pass+".gif";
				timer1->Interval=10;
				timer1->Enabled=true;
			 }
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 pictureBox2->Invalidate();
		 }
};
}
