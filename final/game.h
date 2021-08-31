#pragma once
#define PHYSICS_A 1									//�����[�t��
#define PHYSICS_G 2									//���O�[�t��
#define PHYSICS_V_MAX 8								//�����t�׳̤j��
#define PHYSICS_RISIST_A 1							//���O�[�t��
#define PHYSICS_BACKGROUND_V_MAX 8					//�I���t�׳̤j��
#define PHYSICS_BACKGROUND_A 1						//�I���[�t��
#define PHYSICS_BACKGROUND_TICK_PER_SPEEDUP 512		//�I���[�t���j
#define PHYSICS_WHEEL_SPEED 5						//�u�ʦa�O�t��
#define PHYSICS_ITEM_A 2							//�[�t�D�㨫���[�t��
#define PHYSICS_ITEM_V_MAX 12						//�[�t�D������t�׳̤j��

#include <time.h>
#include <stdlib.h>
#include "rank_record.h"

namespace final {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// game ���K�n
	/// </summary>
	public ref class game : public System::Windows::Forms::Form
	{
	public:
		game(bool^ mode, bool ^music, bool ^sound, bool ^item, bool ^invincible, Byte ^set_diffculty)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X

			srand((unsigned)time(NULL));
			
			//setting parse
			mario_invincible = gcnew short(*invincible);
			luigi_invincible = gcnew short(*invincible);
			if (*invincible || *mode)
			{
				this->label_score->Text = L"";
			}
			else
			{
				this->label_score->Text = L"0";
			}
			if (*mode)
			{
				this->pictureBox_luigi->Enabled = true;
				this->status->BackgroundImage = Image::FromFile(Application::StartupPath + "\\img\\game_2p_status_background.png");
			}
			else
			{
				this->pictureBox_luigi->Enabled = false;
				pictureBox_2p_health->Image = nullptr;
				pictureBox_2p_item->Image = nullptr;
				pictureBox_2p_health->Visible = false;
				pictureBox_2p_item->Visible = false;
				this->label_score->Size = System::Drawing::Size(420, 48);
			}

			setting_difficulty = gcnew Byte(*set_diffculty - 1); //���׼v�T���x�����X�{���v

			setting_item = gcnew bool(*item);
			
			//background music
			this->axWindowsMediaPlayer_background_music->settings->autoStart = false;
			this->axWindowsMediaPlayer_background_music->settings->volume = 100;
			this->axWindowsMediaPlayer_background_music->settings->setMode("loop", true);
			if (*music)
			{
				this->axWindowsMediaPlayer_background_music->URL = Application::StartupPath + "\\music\\game.wav";
				this->axWindowsMediaPlayer_background_music->Ctlcontrols->play();
			}




			//sound
			setting_sound = gcnew bool(*sound);
			if (*sound)
			{
				this->axWindowsMediaPlayer_sound_get_item->settings->autoStart = false;
				this->axWindowsMediaPlayer_sound_get_item->settings->volume = 100;
				this->axWindowsMediaPlayer_sound_get_item->URL = Application::StartupPath + "\\sound\\get_item.wav";
				this->axWindowsMediaPlayer_sound_use_item->settings->autoStart = false;
				this->axWindowsMediaPlayer_sound_use_item->settings->volume = 100;
				this->axWindowsMediaPlayer_sound_use_item->URL = Application::StartupPath + "\\sound\\use_item.wav";
				stab_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\stab.wav");
				fall_down_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\fall_down.wav");
				spring_platform_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\spring_platform.wav");
				jump_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\player_jump.wav");
				win_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\win.wav");
				death_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\death.wav");
				stamp_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\stamp.wav");
				bump_sound = gcnew System::Media::SoundPlayer(Application::StartupPath + "\\sound\\bump.wav");
			}
			


			//health image
			mario_health_image = gcnew array<Bitmap^>(11);
			mario_health_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_0.png");
			mario_health_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_1.png");
			mario_health_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_2.png");
			mario_health_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_3.png");
			mario_health_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_4.png");
			mario_health_image[5] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_5.png");
			mario_health_image[6] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_6.png");
			mario_health_image[7] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_7.png");
			mario_health_image[8] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_8.png");
			mario_health_image[9] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_9.png");
			mario_health_image[10] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_hp_10.png");
			if (*mode)
			{
				luigi_health_image = gcnew array<Bitmap^>(11);
				luigi_health_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_0.png");
				luigi_health_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_1.png");
				luigi_health_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_2.png");
				luigi_health_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_3.png");
				luigi_health_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_4.png");
				luigi_health_image[5] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_5.png");
				luigi_health_image[6] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_6.png");
				luigi_health_image[7] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_7.png");
				luigi_health_image[8] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_8.png");
				luigi_health_image[9] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_9.png");
				luigi_health_image[10] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_hp_10.png");
			}
			


			//mario image
			mario_image = gcnew array<Bitmap^>(8);
			mario_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_stand_right.png");
			mario_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_walk_right.png");
			mario_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_jump_right.png");
			mario_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_stop_right.png");
			mario_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_stand_left.png");
			mario_image[5] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_walk_left.png");
			mario_image[6] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_jump_left.png");
			mario_image[7] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mario_stop_left.png");

			//luigi image
			if (*mode)
			{
				luigi_image = gcnew array<Bitmap^>(8);
				luigi_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_stand_right.png");
				luigi_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_walk_right.png");
				luigi_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_jump_right.png");
				luigi_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_stop_right.png");
				luigi_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_stand_left.png");
				luigi_image[5] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_walk_left.png");
				luigi_image[6] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_jump_left.png");
				luigi_image[7] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\luigi_stop_left.png");
			}
			
			//platform image
			platform_image = gcnew array<Bitmap^>(8);
			platform_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\platform_ground.png");
			platform_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\platform_cloud.png");
			platform_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\platform_eyes_cloud.png");
			platform_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\platform_log_left.png");
			platform_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\platform_log_right.png");
			platform_image[5] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\platform_spike.png");
			platform_image[6] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\platform_mushroom.png");

			//item image
			item_image = gcnew array<Bitmap^>(5);
			item_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\itemcolumn_off.png");//�D��Ҧ����ҥΪ��D����A�D�D��A�Q�ΪŶ�
			item_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\item_mushroom.png");
			item_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\item_star.png");
			item_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\item_speed.png");
			item_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\item_clock.png");
			buff_image = gcnew array<Bitmap^>(2);
			buff_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\buff_star.png");
			buff_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\buff_speedup.png");
			itemcolumn_image = gcnew array<Bitmap^>(5);
			itemcolumn_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\itemcolumn_none.png");
			itemcolumn_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\itemcolumn_mushroom.png");
			itemcolumn_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\itemcolumn_star.png");
			itemcolumn_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\itemcolumn_speed.png");
			itemcolumn_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\itemcolumn_clock.png");
			if (*item)
			{
				this->pictureBox_1p_item->Image = itemcolumn_image[0];
				if (*mode)
				{
					this->pictureBox_2p_item->Image = itemcolumn_image[0];
				}
			}
			else
			{
				this->pictureBox_1p_item->Image = item_image[0];
				if (*mode)
				{
					this->pictureBox_2p_item->Image = item_image[0];
				}
			}

			//effect image
			effect_image = gcnew array<Bitmap^>(3);
			effect_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\effect_jump_0.png");
			effect_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\effect_jump_1.png");
			effect_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\effect_jump_2.png");

			//monster image
			monster_image = gcnew array<Bitmap^>(8);
			monster_image[0] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mush_stand.png");
			monster_image[1] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mush_walk.png");
			monster_image[2] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\mush_death.png");
			monster_image[3] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\turtle_stand_right.png");
			monster_image[4] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\turtle_walk_right.png");
			monster_image[5] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\turtle_stand_left.png");
			monster_image[6] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\turtle_walk_left.png");
			monster_image[7] = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\turtle_death.png");


			//background image
			spike_image = (Bitmap^)Image::FromFile(Application::StartupPath + "\\img\\spike.png");

			//mario variable
			mario_hp = gcnew SByte(10);
			mario_stand = gcnew bool(true);
			mario_falling = gcnew bool(true);
			mario_stop = gcnew bool(false);
			mario_turn_right = gcnew bool(true);
			mario_press_right = gcnew bool(false);
			mario_press_left = gcnew bool(false);
			mario_move_count = gcnew Byte(8);
			mario_v_velocity = gcnew SByte(0);
			mario_h_velocity = gcnew SByte(0);
			mario_current_platform = gcnew SByte(-1);
			mario_effect_platform = gcnew SByte(-1);
			mario_item = gcnew Byte(0);
			mario_speedup = gcnew short(0);
			mario_effect_count = gcnew SByte(0);

			//luigi variable
			luigi_hp = gcnew SByte(10);
			luigi_stand = gcnew bool(true);
			luigi_falling = gcnew bool(true);
			luigi_stop = gcnew bool(false);
			luigi_turn_right = gcnew bool(false);
			luigi_press_right = gcnew bool(false);
			luigi_press_left = gcnew bool(false);
			luigi_move_count = gcnew Byte(8);
			luigi_v_velocity = gcnew SByte(0);
			luigi_h_velocity = gcnew SByte(0);
			luigi_current_platform = gcnew SByte(-1);
			luigi_effect_platform = gcnew SByte(-1);
			luigi_item = gcnew Byte(0);
			luigi_speedup = gcnew short(0);
			luigi_effect_count = gcnew SByte(0);

			//platform control
			platform_list = gcnew array<PictureBox^>(10);
			platform_list[0] = pictureBox_space0;
			platform_list[1] = pictureBox_space1;
			platform_list[2] = pictureBox_space2;
			platform_list[3] = pictureBox_space3;
			platform_list[4] = pictureBox_space4;
			platform_list[5] = pictureBox_space5;
			platform_list[6] = pictureBox_space6;
			platform_list[7] = pictureBox_space7;
			platform_list[8] = pictureBox_space8;
			platform_list[9] = pictureBox_space9;
			platform_kind = gcnew array<Byte>(10);
			platform_count = gcnew Byte(20);
			//�H����l���x
			for (int i = 1; i < platform_list->Length; i++)
			{
				platform_list[i]->Left = (rand() + platform_list[i]->Location.X) % 508;
			}


			//platform appear prob
			platform_kind_prob = gcnew array<int>(4);
			platform_kind_prob[0] = 100 - (*setting_difficulty * 20);
			platform_kind_prob[1] = 0 + (*setting_difficulty * 10);
			platform_kind_prob[2] = 0 + (*setting_difficulty * 5);
			platform_kind_prob[3] = 0 + (*setting_difficulty * 5);

			//item control
			item_kind = gcnew Byte(0);

			//monster control
			monster_move_count = gcnew Byte(0);
			monster_death_count = gcnew Byte(0);
			monster_current_platform = gcnew SByte(-1);
			monster_turn_right = gcnew bool(true);
			monster_stand = gcnew bool(true);
			monster_kind = gcnew Byte(0);
			monster_target = gcnew Byte(0);

			//background control
			time_count = gcnew short(0);
			background_speed = gcnew Byte(3);
			score = gcnew int(0);
			time_freeze = gcnew short(0);
		}
	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~game()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox_item;
	private: System::Windows::Forms::FlowLayoutPanel^  status;
	private: System::Windows::Forms::PictureBox^  pictureBox_1p_health;
	private: System::Windows::Forms::PictureBox^  pictureBox_2p_health;
	private: System::Windows::Forms::PictureBox^  pictureBox_1p_item;
	private: System::Windows::Forms::PictureBox^  pictureBox_2p_item;
	private: System::Windows::Forms::Label^  label_score;
	private: System::Windows::Forms::PictureBox^  pictureBox_spike;
	private: System::Windows::Forms::PictureBox^  pictureBox_mario;
	private: System::Windows::Forms::PictureBox^  pictureBox_luigi; 
	private: System::Windows::Forms::PictureBox^  pictureBox_mario_effect;
	private: System::Windows::Forms::PictureBox^  pictureBox_luigi_effect;
	private: System::Windows::Forms::PictureBox^  pictureBox_space0;
	private: System::Windows::Forms::PictureBox^  pictureBox_space1;
	private: System::Windows::Forms::PictureBox^  pictureBox_space2;
	private: System::Windows::Forms::PictureBox^  pictureBox_space3;
	private: System::Windows::Forms::PictureBox^  pictureBox_space4;
	private: System::Windows::Forms::PictureBox^  pictureBox_space5;
	private: System::Windows::Forms::PictureBox^  pictureBox_space6;
	private: System::Windows::Forms::PictureBox^  pictureBox_space7;
	private: System::Windows::Forms::PictureBox^  pictureBox_space8;
	private: System::Windows::Forms::PictureBox^  pictureBox_space9;
	private: System::Windows::Forms::PictureBox^  pictureBox_monster;
	private: System::Windows::Forms::Timer^  timer_game;
	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer_background_music;
	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer_sound_get_item;
	private: AxWMPLib::AxWindowsMediaPlayer^  axWindowsMediaPlayer_sound_use_item;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		//setting
		bool ^setting_item = nullptr;
		bool ^setting_sound = nullptr;
		Byte ^setting_difficulty = nullptr;

		//sound
		System::Media::SoundPlayer^ stab_sound = nullptr;
		System::Media::SoundPlayer^ fall_down_sound = nullptr;
		System::Media::SoundPlayer^ spring_platform_sound = nullptr;
		System::Media::SoundPlayer^ jump_sound = nullptr;
		System::Media::SoundPlayer^ win_sound = nullptr;
		System::Media::SoundPlayer^ death_sound = nullptr;
		System::Media::SoundPlayer^ stamp_sound = nullptr;
		System::Media::SoundPlayer^ bump_sound = nullptr;

		//Image
		Bitmap^ spike_image = nullptr;
		array<Bitmap^>^ mario_image = nullptr;
		array<Bitmap^>^ luigi_image = nullptr;
		array<Bitmap^>^ mario_health_image = nullptr;
		array<Bitmap^>^ luigi_health_image = nullptr;
		array<Bitmap^>^ item_image = nullptr;
		array<Bitmap^>^ itemcolumn_image = nullptr;
		array<Bitmap^>^ buff_image = nullptr;
		array<Bitmap^>^ effect_image = nullptr;
		array<Bitmap^>^ monster_image = nullptr;

		//platform control
		array<PictureBox^>^ platform_list = nullptr;
		array<Byte>^ platform_kind = nullptr;
		array<int>^ platform_kind_prob = nullptr;
		array<Bitmap^>^ platform_image = nullptr;
		Byte^ platform_count = nullptr;

		//mario control
		bool^ mario_stand = nullptr;
		bool^ mario_falling = nullptr;
		bool^ mario_stop = nullptr;
		bool^ mario_turn_right = nullptr;
		bool^ mario_press_right = nullptr;
		bool^ mario_press_left = nullptr;
		SByte^ mario_v_velocity = nullptr;
		SByte^ mario_h_velocity = nullptr;
		SByte^ mario_current_platform = nullptr;
		SByte^ mario_effect_platform = nullptr;
		short^ mario_invincible = nullptr;
		short^ mario_speedup = nullptr;
		Byte^ mario_move_count = nullptr;
		SByte^ mario_hp = nullptr;;
		Byte^ mario_item = nullptr;

		//luigi control
		bool^ luigi_stand = nullptr;
		bool^ luigi_falling = nullptr;
		bool^ luigi_stop = nullptr;
		bool^ luigi_turn_right = nullptr;
		bool^ luigi_press_right = nullptr;
		bool^ luigi_press_left = nullptr;
		short^ luigi_invincible = nullptr;
		short^ luigi_speedup = nullptr;
		SByte^ luigi_v_velocity = nullptr;
		SByte^ luigi_h_velocity = nullptr;
		SByte^ luigi_current_platform = nullptr;
		SByte^ luigi_effect_platform = nullptr;
		Byte^ luigi_move_count = nullptr;
		SByte^ luigi_hp = nullptr;
		Byte^ luigi_item = nullptr;

		//background control
		short^ time_count = nullptr;
		int^ score = nullptr;
		Byte^ background_speed = nullptr;
		short^ time_freeze = nullptr;
		SByte^ mario_effect_count = nullptr;
		SByte^ luigi_effect_count = nullptr;

		//item control
		Byte^ item_kind = nullptr;

		//monster control
		bool^ monster_turn_right = nullptr;
		bool^ monster_stand = nullptr;
		Byte^ monster_kind = nullptr;
		Byte^ monster_move_count = nullptr;
		Byte^ monster_death_count = nullptr;
		SByte^ monster_current_platform = nullptr;
		Byte^ monster_target = nullptr;


		//function
		void touch_spike(bool^ mario, bool^ platform, bool^ fall)
		{
			if (*mario)
			{
				if (!*mario_invincible)
				{
					if(*setting_sound)
						stab_sound->Play();
					if (*platform)
					{
						if (*mario_hp >= 4)
							*mario_hp -= 4;
						else
							*mario_hp = 0;
					}
					else
					{
						if (*mario_hp >= 3)
							*mario_hp -= 3;
						else
							*mario_hp = 0;
					}
				}
				if (*fall)
					*mario_hp = 0;
				if (*mario_hp <= 0)
				{//Death
					//����
					if (*setting_sound)
						death_sound->Play();
					this->pictureBox_1p_health->Image = mario_health_image[0];
					this->timer_game->Enabled = false;
					this->timer_game->~Timer();
					this->axWindowsMediaPlayer_background_music->Ctlcontrols->stop();
					if (pictureBox_luigi->Enabled)
					{
						//����
						if (*setting_sound)
							win_sound->Play();
						MessageBox::Show(
							"2P WIN",
							"���", MessageBoxButtons::OK,
							MessageBoxIcon::None);
					}
					else
					{
						rank_record ^form_a = gcnew rank_record(*score);
						form_a->ShowDialog();
					}
					this->Close();
				}
				else
				{//����S��
					if (*platform)
					{//���x
						this->pictureBox_1p_health->Image = mario_health_image[*mario_hp];
					}
					else
					{//���ݦy��
						this->pictureBox_1p_health->Image = mario_health_image[*mario_hp];
						//���� ���U�� �קK�s�򦩦� �P�ɬ��F�קK�׸����몽������ �ҥH�n�N��l�t�ױj��վ�
						*mario_falling = true;
						*mario_current_platform = -1;
						*mario_v_velocity = 3;
						this->pictureBox_mario->Top = this->pictureBox_spike->Height + this->status->Height + 10;
					}
				}
			}
			else
			{
				if (!*luigi_invincible)
				{
					if (*setting_sound)
						stab_sound->Play();
					if (*platform)
					{
						if (*luigi_hp >= 4)
							*luigi_hp -= 4;
						else
							*luigi_hp = 0;
					}
					else
					{
						if (*luigi_hp >= 3)
							*luigi_hp -= 3;
						else
							*luigi_hp = 0;
					}
				}
				if (*fall)
					*luigi_hp = 0;
				if (*luigi_hp <= 0)
				{//Death
					this->pictureBox_2p_health->Image = luigi_health_image[0];
					this->timer_game->Enabled = false;
					this->axWindowsMediaPlayer_background_music->Ctlcontrols->stop();
					//����
					if (*setting_sound)
						win_sound->Play();
					MessageBox::Show(
						"1P WIN",
						"���", MessageBoxButtons::OK,
						MessageBoxIcon::None);
					this->Close();
				}
				else
				{//����S��
					if (*platform)
					{//���x
						this->pictureBox_2p_health->Image = luigi_health_image[*luigi_hp];
					}
					else
					{//���ݦy��
						this->pictureBox_2p_health->Image = luigi_health_image[*luigi_hp];
						//���� ���U�� �קK�s�򦩦� �P�ɬ��F�קK�׸����몽������ �ҥH�n�N��l�t�ױj��վ�
						*luigi_falling = true;
						*luigi_current_platform = -1;
						*luigi_v_velocity = 3;
						this->pictureBox_luigi->Top = this->pictureBox_spike->Height + this->status->Height + 10;
					}
				}
			}
			return;
		}

		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(game::typeid));
			this->status = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBox_2p_item = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_2p_health = (gcnew System::Windows::Forms::PictureBox());
			this->label_score = (gcnew System::Windows::Forms::Label());
			this->pictureBox_1p_health = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_1p_item = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_item = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space0 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_space1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_spike = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_mario = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_luigi = (gcnew System::Windows::Forms::PictureBox());
			this->timer_game = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox_mario_effect = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_luigi_effect = (gcnew System::Windows::Forms::PictureBox());
			this->axWindowsMediaPlayer_background_music = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->pictureBox_monster = (gcnew System::Windows::Forms::PictureBox());
			this->axWindowsMediaPlayer_sound_get_item = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->axWindowsMediaPlayer_sound_use_item = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->status->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p_item))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p_health))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p_health))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p_item))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_item))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space0))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_spike))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_mario))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_luigi))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_mario_effect))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_luigi_effect))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_background_music))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_monster))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_sound_get_item))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_sound_use_item))->BeginInit();
			this->SuspendLayout();
			// 
			// status
			// 
			this->status->BackColor = System::Drawing::Color::Transparent;
			this->status->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"status.BackgroundImage")));
			this->status->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->status->Controls->Add(this->pictureBox_2p_item);
			this->status->Controls->Add(this->pictureBox_2p_health);
			this->status->Controls->Add(this->label_score);
			this->status->Controls->Add(this->pictureBox_1p_health);
			this->status->Controls->Add(this->pictureBox_1p_item);
			this->status->Location = System::Drawing::Point(0, -1);
			this->status->Name = L"status";
			this->status->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->status->Size = System::Drawing::Size(700, 54);
			this->status->TabIndex = 1;
			// 
			// pictureBox_2p_item
			// 
			this->pictureBox_2p_item->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_2p_item->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_2p_item.Image")));
			this->pictureBox_2p_item->Location = System::Drawing::Point(3, 7);
			this->pictureBox_2p_item->Margin = System::Windows::Forms::Padding(3, 7, 3, 3);
			this->pictureBox_2p_item->Name = L"pictureBox_2p_item";
			this->pictureBox_2p_item->Size = System::Drawing::Size(40, 40);
			this->pictureBox_2p_item->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_2p_item->TabIndex = 6;
			this->pictureBox_2p_item->TabStop = false;
			// 
			// pictureBox_2p_health
			// 
			this->pictureBox_2p_health->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_2p_health->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_2p_health.Image")));
			this->pictureBox_2p_health->Location = System::Drawing::Point(49, 7);
			this->pictureBox_2p_health->Margin = System::Windows::Forms::Padding(3, 7, 3, 3);
			this->pictureBox_2p_health->Name = L"pictureBox_2p_health";
			this->pictureBox_2p_health->Size = System::Drawing::Size(220, 40);
			this->pictureBox_2p_health->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_2p_health->TabIndex = 5;
			this->pictureBox_2p_health->TabStop = false;
			// 
			// label_score
			// 
			this->label_score->BackColor = System::Drawing::Color::Transparent;
			this->label_score->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 26, System::Drawing::FontStyle::Bold));
			this->label_score->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label_score->Location = System::Drawing::Point(275, 3);
			this->label_score->Margin = System::Windows::Forms::Padding(3);
			this->label_score->Name = L"label_score";
			this->label_score->Size = System::Drawing::Size(150, 48);
			this->label_score->TabIndex = 7;
			// 
			// pictureBox_1p_health
			// 
			this->pictureBox_1p_health->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_1p_health->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_1p_health.Image")));
			this->pictureBox_1p_health->Location = System::Drawing::Point(431, 7);
			this->pictureBox_1p_health->Margin = System::Windows::Forms::Padding(3, 7, 3, 3);
			this->pictureBox_1p_health->Name = L"pictureBox_1p_health";
			this->pictureBox_1p_health->Size = System::Drawing::Size(220, 40);
			this->pictureBox_1p_health->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_1p_health->TabIndex = 2;
			this->pictureBox_1p_health->TabStop = false;
			// 
			// pictureBox_1p_item
			// 
			this->pictureBox_1p_item->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_1p_item->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->pictureBox_1p_item->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_1p_item.Image")));
			this->pictureBox_1p_item->Location = System::Drawing::Point(657, 7);
			this->pictureBox_1p_item->Margin = System::Windows::Forms::Padding(3, 7, 3, 3);
			this->pictureBox_1p_item->Name = L"pictureBox_1p_item";
			this->pictureBox_1p_item->Size = System::Drawing::Size(40, 40);
			this->pictureBox_1p_item->TabIndex = 4;
			this->pictureBox_1p_item->TabStop = false;
			// 
			// pictureBox_item
			// 
			this->pictureBox_item->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_item->Enabled = false;
			this->pictureBox_item->Location = System::Drawing::Point(85, 398);
			this->pictureBox_item->Name = L"pictureBox_item";
			this->pictureBox_item->Size = System::Drawing::Size(32, 32);
			this->pictureBox_item->TabIndex = 12;
			this->pictureBox_item->TabStop = false;
			this->pictureBox_item->Visible = false;
			// 
			// pictureBox_space0
			// 
			this->pictureBox_space0->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space0->Location = System::Drawing::Point(256, 346);
			this->pictureBox_space0->Name = L"pictureBox_space0";
			this->pictureBox_space0->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space0->TabIndex = 11;
			this->pictureBox_space0->TabStop = false;
			this->pictureBox_space0->Visible = false;
			// 
			// pictureBox_space9
			// 
			this->pictureBox_space9->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space9->Location = System::Drawing::Point(460, 700);
			this->pictureBox_space9->Name = L"pictureBox_space9";
			this->pictureBox_space9->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space9->TabIndex = 10;
			this->pictureBox_space9->TabStop = false;
			this->pictureBox_space9->Visible = false;
			// 
			// pictureBox_space7
			// 
			this->pictureBox_space7->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space7->Location = System::Drawing::Point(50, 561);
			this->pictureBox_space7->Name = L"pictureBox_space7";
			this->pictureBox_space7->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space7->TabIndex = 9;
			this->pictureBox_space7->TabStop = false;
			this->pictureBox_space7->Visible = false;
			// 
			// pictureBox_space8
			// 
			this->pictureBox_space8->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space8->Location = System::Drawing::Point(256, 631);
			this->pictureBox_space8->Name = L"pictureBox_space8";
			this->pictureBox_space8->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space8->TabIndex = 8;
			this->pictureBox_space8->TabStop = false;
			this->pictureBox_space8->Visible = false;
			// 
			// pictureBox_space6
			// 
			this->pictureBox_space6->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space6->Location = System::Drawing::Point(460, 491);
			this->pictureBox_space6->Name = L"pictureBox_space6";
			this->pictureBox_space6->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space6->TabIndex = 7;
			this->pictureBox_space6->TabStop = false;
			this->pictureBox_space6->Visible = false;
			// 
			// pictureBox_space5
			// 
			this->pictureBox_space5->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space5->Location = System::Drawing::Point(26, 430);
			this->pictureBox_space5->Name = L"pictureBox_space5";
			this->pictureBox_space5->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space5->TabIndex = 6;
			this->pictureBox_space5->TabStop = false;
			this->pictureBox_space5->Visible = false;
			// 
			// pictureBox_space4
			// 
			this->pictureBox_space4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space4->Location = System::Drawing::Point(460, 252);
			this->pictureBox_space4->Name = L"pictureBox_space4";
			this->pictureBox_space4->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space4->TabIndex = 5;
			this->pictureBox_space4->TabStop = false;
			this->pictureBox_space4->Visible = false;
			// 
			// pictureBox_space3
			// 
			this->pictureBox_space3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space3->Location = System::Drawing::Point(1, 184);
			this->pictureBox_space3->Name = L"pictureBox_space3";
			this->pictureBox_space3->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space3->TabIndex = 4;
			this->pictureBox_space3->TabStop = false;
			this->pictureBox_space3->Visible = false;
			// 
			// pictureBox_space2
			// 
			this->pictureBox_space2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space2->Location = System::Drawing::Point(1, 120);
			this->pictureBox_space2->Name = L"pictureBox_space2";
			this->pictureBox_space2->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space2->TabIndex = 3;
			this->pictureBox_space2->TabStop = false;
			this->pictureBox_space2->Visible = false;
			// 
			// pictureBox_space1
			// 
			this->pictureBox_space1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_space1->Location = System::Drawing::Point(1, 57);
			this->pictureBox_space1->Name = L"pictureBox_space1";
			this->pictureBox_space1->Size = System::Drawing::Size(192, 32);
			this->pictureBox_space1->TabIndex = 1;
			this->pictureBox_space1->TabStop = false;
			this->pictureBox_space1->Visible = false;
			// 
			// pictureBox_spike
			// 
			this->pictureBox_spike->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_spike->Location = System::Drawing::Point(1, 53);
			this->pictureBox_spike->Name = L"pictureBox_spike";
			this->pictureBox_spike->Size = System::Drawing::Size(700, 32);
			this->pictureBox_spike->TabIndex = 0;
			this->pictureBox_spike->TabStop = false;
			this->pictureBox_spike->Visible = false;
			// 
			// pictureBox_mario
			// 
			this->pictureBox_mario->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_mario->Location = System::Drawing::Point(378, 264);
			this->pictureBox_mario->Name = L"pictureBox_mario";
			this->pictureBox_mario->Size = System::Drawing::Size(48, 48);
			this->pictureBox_mario->TabIndex = 2;
			this->pictureBox_mario->TabStop = false;
			this->pictureBox_mario->Visible = false;
			// 
			// pictureBox_luigi
			// 
			this->pictureBox_luigi->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_luigi->Enabled = false;
			this->pictureBox_luigi->Location = System::Drawing::Point(276, 264);
			this->pictureBox_luigi->Name = L"pictureBox_luigi";
			this->pictureBox_luigi->Size = System::Drawing::Size(48, 48);
			this->pictureBox_luigi->TabIndex = 13;
			this->pictureBox_luigi->TabStop = false;
			this->pictureBox_luigi->Visible = false;
			// 
			// timer_game
			// 
			this->timer_game->Enabled = true;
			this->timer_game->Interval = 30;
			this->timer_game->Tick += gcnew System::EventHandler(this, &game::timer_game_Tick);
			// 
			// pictureBox_mario_effect
			// 
			this->pictureBox_mario_effect->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_mario_effect->Location = System::Drawing::Point(668, 147);
			this->pictureBox_mario_effect->Name = L"pictureBox_mario_effect";
			this->pictureBox_mario_effect->Size = System::Drawing::Size(80, 26);
			this->pictureBox_mario_effect->TabIndex = 14;
			this->pictureBox_mario_effect->TabStop = false;
			this->pictureBox_mario_effect->Visible = false;
			// 
			// pictureBox_luigi_effect
			// 
			this->pictureBox_luigi_effect->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_luigi_effect->Location = System::Drawing::Point(668, 102);
			this->pictureBox_luigi_effect->Name = L"pictureBox_luigi_effect";
			this->pictureBox_luigi_effect->Size = System::Drawing::Size(80, 26);
			this->pictureBox_luigi_effect->TabIndex = 15;
			this->pictureBox_luigi_effect->TabStop = false;
			this->pictureBox_luigi_effect->Visible = false;
			// 
			// axWindowsMediaPlayer_background_music
			// 
			this->axWindowsMediaPlayer_background_music->Enabled = true;
			this->axWindowsMediaPlayer_background_music->Location = System::Drawing::Point(683, 193);
			this->axWindowsMediaPlayer_background_music->Name = L"axWindowsMediaPlayer_background_music";
			this->axWindowsMediaPlayer_background_music->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer_background_music.OcxState")));
			this->axWindowsMediaPlayer_background_music->Size = System::Drawing::Size(75, 23);
			this->axWindowsMediaPlayer_background_music->TabIndex = 16;
			this->axWindowsMediaPlayer_background_music->TabStop = false;
			this->axWindowsMediaPlayer_background_music->Visible = false;
			// 
			// pictureBox_monster
			// 
			this->pictureBox_monster->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox_monster->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->pictureBox_monster->Enabled = false;
			this->pictureBox_monster->Location = System::Drawing::Point(534, 430);
			this->pictureBox_monster->Name = L"pictureBox_monster";
			this->pictureBox_monster->Size = System::Drawing::Size(32, 32);
			this->pictureBox_monster->TabIndex = 17;
			this->pictureBox_monster->TabStop = false;
			this->pictureBox_monster->Visible = false;
			// 
			// axWindowsMediaPlayer_sound_get_item
			// 
			this->axWindowsMediaPlayer_sound_get_item->Enabled = true;
			this->axWindowsMediaPlayer_sound_get_item->Location = System::Drawing::Point(683, 222);
			this->axWindowsMediaPlayer_sound_get_item->Name = L"axWindowsMediaPlayer_sound_get_item";
			this->axWindowsMediaPlayer_sound_get_item->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer_sound_get_item.OcxState")));
			this->axWindowsMediaPlayer_sound_get_item->Size = System::Drawing::Size(75, 23);
			this->axWindowsMediaPlayer_sound_get_item->TabIndex = 18;
			this->axWindowsMediaPlayer_sound_get_item->TabStop = false;
			this->axWindowsMediaPlayer_sound_get_item->Visible = false;
			// 
			// axWindowsMediaPlayer_sound_use_item
			// 
			this->axWindowsMediaPlayer_sound_use_item->Enabled = true;
			this->axWindowsMediaPlayer_sound_use_item->Location = System::Drawing::Point(683, 252);
			this->axWindowsMediaPlayer_sound_use_item->Name = L"axWindowsMediaPlayer_sound_use_item";
			this->axWindowsMediaPlayer_sound_use_item->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer_sound_use_item.OcxState")));
			this->axWindowsMediaPlayer_sound_use_item->Size = System::Drawing::Size(75, 23);
			this->axWindowsMediaPlayer_sound_use_item->TabIndex = 19;
			this->axWindowsMediaPlayer_sound_use_item->TabStop = false;
			this->axWindowsMediaPlayer_sound_use_item->Visible = false;
			// 
			// game
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(700, 715);
			this->Controls->Add(this->axWindowsMediaPlayer_sound_use_item);
			this->Controls->Add(this->axWindowsMediaPlayer_sound_get_item);
			this->Controls->Add(this->pictureBox_monster);
			this->Controls->Add(this->axWindowsMediaPlayer_background_music);
			this->Controls->Add(this->pictureBox_luigi_effect);
			this->Controls->Add(this->pictureBox_mario_effect);
			this->Controls->Add(this->pictureBox_spike);
			this->Controls->Add(this->status);
			this->Controls->Add(this->pictureBox_space6);
			this->Controls->Add(this->pictureBox_item);
			this->Controls->Add(this->pictureBox_space4);
			this->Controls->Add(this->pictureBox_space5);
			this->Controls->Add(this->pictureBox_space0);
			this->Controls->Add(this->pictureBox_space3);
			this->Controls->Add(this->pictureBox_space2);
			this->Controls->Add(this->pictureBox_space9);
			this->Controls->Add(this->pictureBox_space7);
			this->Controls->Add(this->pictureBox_space8);
			this->Controls->Add(this->pictureBox_space1);
			this->Controls->Add(this->pictureBox_mario);
			this->Controls->Add(this->pictureBox_luigi);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"game";
			this->Text = L"game";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &game::game_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &game::game_KeyUp);
			this->status->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p_item))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_2p_health))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p_health))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_1p_item))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_item))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space0))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_space1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_spike))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_mario))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_luigi))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_mario_effect))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_luigi_effect))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_background_music))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_monster))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_sound_get_item))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer_sound_use_item))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void game_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Left )
	{
		if (!*mario_press_left)
		{
			*mario_press_left = true;
		}
	}
	if (e->KeyCode == Keys::Right)
	{
		if (!*mario_press_right)
		{
			*mario_press_right = true;
		}
	}
	if (e->KeyCode == Keys::Up && !*mario_falling)
	{
		//����
		if (*setting_sound)
			jump_sound->Play();
		*mario_v_velocity -= 18;
		this->pictureBox_mario->Top -= 2;
		*mario_falling = true;
		*mario_current_platform = -1;
	}
	if (e->KeyCode == Keys::Down &&	*mario_item)
	{
		//����
		if (*setting_sound)
			this->axWindowsMediaPlayer_sound_use_item->Ctlcontrols->play();
		switch (*mario_item)
		{
		case 1:
			*mario_hp = 10;
			this->pictureBox_1p_health->Image = mario_health_image[10];
			break;
		case 2:
			if (*mario_invincible != 1)
				*mario_invincible = -166;
			break;
		case 3:
			*mario_speedup = -166;
			break;
		case 4:
			*time_freeze = -166;
			break;
		}
		*mario_item = 0;
		this->pictureBox_1p_item->Image = itemcolumn_image[0];
	}
	if (pictureBox_luigi->Enabled)
	{
		if (e->KeyCode == Keys::A)
		{
			if (!*luigi_press_left)
			{
				*luigi_press_left = true;
			}
		}
		if (e->KeyCode == Keys::D)
		{
			if (!*luigi_press_right)
			{
				*luigi_press_right = true;
			}
		}
		if (e->KeyCode == Keys::W && !*luigi_falling)
		{
			//����
			if (*setting_sound)
				jump_sound->Play();
			*luigi_v_velocity -= 18;
			this->pictureBox_luigi->Top -= 2;
			*luigi_falling = true;
			*luigi_current_platform = -1;
		}
		if (e->KeyCode == Keys::S && *luigi_item)
		{
			//����
			if (*setting_sound)
				this->axWindowsMediaPlayer_sound_use_item->Ctlcontrols->play();
			switch (*luigi_item)
			{
			case 1:
				*luigi_hp = 10;
				this->pictureBox_2p_health->Image = luigi_health_image[10];
				break;
			case 2:
				if (*luigi_invincible != 1)
					*luigi_invincible = -166;
				break;
			case 3:
				*luigi_speedup = -166;
				break;
			case 4:
				*time_freeze = -166;
				break;
			}
			*luigi_item = 0;
			this->pictureBox_2p_item->Image = itemcolumn_image[0];
		}
	}
	return;
}
private: System::Void game_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Left )
	{
		*mario_press_left = false;
	}
	if (e->KeyCode == Keys::Right )
	{
		*mario_press_right = false;
	}
	if (pictureBox_luigi->Enabled)
	{
		if (e->KeyCode == Keys::A)
		{
			*luigi_press_left = false;
		}
		if (e->KeyCode == Keys::D)
		{
			*luigi_press_right = false;
		}
	}
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
private: System::Void timer_game_Tick(System::Object^  sender, System::EventArgs^  e) {
	static int i, x, y;
	static bool mario_rolling_status, mario_rolling_right, mario_mushroom_status;
	static bool luigi_rolling_status, luigi_rolling_right, luigi_mushroom_status;
	static int prob;
	static bool new_platform;
	//////////////////////////////////////////////////////////
	//			    _____      _   _   _             
	//			   / ____|    | | | | (_)            
	//			  | (___   ___| |_| |_ _ _ __   __ _ 
	//			   \___ \ / _ \ __| __| | '_ \ / _` |
	//			   ____) |  __/ |_| |_| | | | | (_| |
	//			  |_____/ \___|\__|\__|_|_| |_|\__, |
	//			                                __/ |
	//			                               |___/
	//////////////////////////////////////////////////////////
	if (!*time_freeze)
	{
		(*time_count)++;
		if(*platform_count)
			(*platform_count)--;
	}
	//�I���[�t
	if (*time_count & PHYSICS_BACKGROUND_TICK_PER_SPEEDUP && *background_speed <  PHYSICS_BACKGROUND_V_MAX)
	{
		switch (*background_speed)
		{
		case 4:
			platform_kind_prob[0] -= 10;
			platform_kind_prob[1] += 10;
			break;
		case 5:
			platform_kind_prob[0] -= 10;
			platform_kind_prob[1] += 10;
			break;
		case 6:
			platform_kind_prob[0] -= 10;
			platform_kind_prob[2] += 5;
			platform_kind_prob[3] += 5;
			break;
		case 7:
			platform_kind_prob[0] -= 10;
			platform_kind_prob[1] += 10;
			break;
		case 8:
			platform_kind_prob[0] -= 10;
			platform_kind_prob[2] += 5;
			platform_kind_prob[3] += 5;
			break;
		}
		*background_speed += PHYSICS_BACKGROUND_A;
		*time_count = 0;
	}
	//��s����
	if (!(*time_count & 31) && *mario_invincible != 1 && !pictureBox_luigi->Enabled)
	{
		//���ƭp��覡 : (�C��s���ƴ`��)
		//�Ĥ@�����x���v * 0.1
		//�ĤG�����x���v * 0.5
		//�ĤT�����x���v * 1
		//�ĥ|�����x���v * 0.8
		//�`�M
		*score += platform_kind_prob[0] * 0.1 + platform_kind_prob[1] * 0.5 + platform_kind_prob[2] * 1 + platform_kind_prob[3] * 0.8;
		this->label_score->Text = score->ToString();
	}
	//�L�ġB�[�t�B�Ȱ��ĪG�p��
	if (*time_freeze)
		(*time_freeze)++;
	if (*mario_invincible < 0)
		(*mario_invincible)++;
	if (*mario_speedup)
		(*mario_speedup)++;
	if (pictureBox_luigi->Enabled)
	{
		if (*luigi_invincible < 0)
			(*luigi_invincible)++;
		if (*luigi_speedup)
			(*luigi_speedup)++;
	}
	//�S�ĭp��
	if (*mario_effect_count)
	{
		if (*mario_effect_count > 0)
			(*mario_effect_count)--;
		else
			(*mario_effect_count)++;
	}
	if (*luigi_effect_count)
	{
		if (*luigi_effect_count > 0)
			(*luigi_effect_count)--;
		else
			(*luigi_effect_count)++;
	}
	//�Ǫ��Ϲ��p��
	if (*monster_death_count)
	{
		(*monster_death_count)--;
		if (!*monster_death_count)
		{
			this->pictureBox_monster->Enabled = false;
			//�ͩǪ��M�ݹD��
			if (!this->pictureBox_item->Enabled)
			{
				if (!*monster_kind)
					*monster_kind = 3;
				this->pictureBox_item->Enabled = true;
				this->pictureBox_item->Top = platform_list[*monster_current_platform]->Top - this->pictureBox_item->Height;
				this->pictureBox_item->Left = this->pictureBox_monster->Left;
				this->pictureBox_item->Image = item_image[*monster_kind];
				*item_kind = *monster_kind;
			}
		}
	}
	if (!*time_freeze && *monster_move_count)
	{
		(*monster_move_count)--;
		if (!*monster_move_count)
		{
			(*monster_move_count) = 6;
			*monster_stand = !*monster_stand;
		}
	}
	//////////////////////////////////////////////////////////
	//			  __  __          _____  _____ ____  
	//			 |  \/  |   /\   |  __ \|_   _/ __ \ 
	//			 | \  / |  /  \  | |__) | | || |  | |
	//			 | |\/| | / /\ \ |  _  /  | || |  | |
	//			 | |  | |/ ____ \| | \ \ _| || |__| |
	//			 |_|  |_/_/    \_\_|  \_\_____\____/ 
	//////////////////////////////////////////////////////////
	//�����t��
	if (*mario_falling)
	{//�b�Ť�
		if (*mario_v_velocity < 0)
		{//���D��
			*mario_v_velocity += PHYSICS_G;
		}
		else
		{//���U��
			//�ĪG�����I
			mario_rolling_status = false;
			mario_mushroom_status = false;

			//�ˬd�Ǫ��u��
			x = this->pictureBox_monster->Left - this->pictureBox_mario->Left;
			y = this->pictureBox_monster->Top - this->pictureBox_mario->Top - this->pictureBox_mario->Height;
			if (this->pictureBox_monster->Enabled && x<48 && x>(-this->pictureBox_monster->Width) && y <= *mario_v_velocity + PHYSICS_G && y >= 0)
			{
				if (*setting_sound)
					stamp_sound->Play();
				*monster_death_count = 5;
				//Jump
				*mario_v_velocity = -18;
				this->pictureBox_mario->Top = this->pictureBox_monster->Top - this->pictureBox_mario->Height - 2;
				*mario_falling = true;
				*mario_current_platform = -1;
			}
			else
			{//�ˬd�U���x
				for (i = 0; i < platform_list->Length; i++)
				{
					if (platform_list[i]->Enabled)
					{
						//�ˬd�p�G�~�򱼷|���|���a
						x = platform_list[i]->Location.X - this->pictureBox_mario->Location.X;
						y = platform_list[i]->Location.Y - 48;
						if (x > -183 && x < 38 && y >= this->pictureBox_mario->Location.Y && y <= this->pictureBox_mario->Location.Y + *mario_v_velocity + PHYSICS_G)
						{//�|���a
							*mario_falling = false;
							*mario_v_velocity = 0;
							//�������ʨ쥭�x�W
							this->pictureBox_mario->Top = platform_list[i]->Location.Y - 48;
							*mario_current_platform = i;
							//����
							if (*setting_sound)
								fall_down_sound->Play();
							//�d�ݥثe���x����
							switch (platform_kind[i])
							{
							case 1:
								//�u��
								*mario_v_velocity -= 18;
								this->pictureBox_mario->Top -= 2;
								*mario_falling = true;
								*mario_current_platform = -1;
								*mario_effect_platform = i;
								*mario_effect_count = 8;
								//����
								if (*setting_sound)
									spring_platform_sound->Play();
								break;
							case 2:
								//�Ť�
								platform_list[i]->Enabled = false;
								*mario_falling = true;
								*mario_current_platform = -1;
								break;
							case 3:
								//�V���u��
								mario_rolling_status = true;
								mario_rolling_right = false;
								break;
							case 4:
								//�V�k�u��
								mario_rolling_status = true;
								mario_rolling_right = true;
								break;
							case 5:
								//�y��
								touch_spike(true, true, false);
								break;
							case 6:
								//�ϦV
								mario_mushroom_status = true;
								break;
							}
							if (*mario_hp < 10)
							{
								*mario_hp += 1;
								this->pictureBox_1p_health->Image = mario_health_image[*mario_hp];
							}
							break;
						}
					}
				}
			}
			if (*mario_falling)
			{//���|���a
				*mario_v_velocity += PHYSICS_G;
			}
		}
	}
	else
	{//�b���x�W
		//�ˬd�O�_�٦b���x�W
		x = platform_list[*mario_current_platform]->Location.X - this->pictureBox_mario->Location.X;
		y = platform_list[*mario_current_platform]->Location.Y - this->pictureBox_mario->Location.Y;
		if (!(x > -183 && x < 38 && y > 16 && y <= 48))
		{//���}���x
			//���ˬd��U�A���ˬd��Tick���ʫ�
			//�۷��O�W��Tick���X���x�~�A�b��Tick�~���U
			*mario_falling = true;
			*mario_v_velocity += PHYSICS_G;
		}
	}

	//�����t��
	*mario_stop = false;
	if (*mario_press_left ^ *mario_press_right)
	{//���k�Ȥ@���U
		//�Y�b�ϦV���x�h�մ���V��
		if (mario_mushroom_status)
		{
			*mario_press_left = !*mario_press_left;
			*mario_press_right = !*mario_press_right;
		}
		//�T�{��V
		*mario_turn_right = *mario_press_right;
		//�p��t�� 
		if (*mario_press_right)
		{
			if (*mario_speedup)
				*mario_h_velocity = (*mario_h_velocity + PHYSICS_ITEM_A) > PHYSICS_ITEM_V_MAX ? PHYSICS_ITEM_V_MAX : (*mario_h_velocity + PHYSICS_ITEM_A);
			else
				*mario_h_velocity = (*mario_h_velocity + PHYSICS_A) > PHYSICS_V_MAX ? PHYSICS_V_MAX : (*mario_h_velocity + PHYSICS_A);
		}
		else
		{
			if (*mario_speedup)
				*mario_h_velocity = (*mario_h_velocity - PHYSICS_ITEM_A) < -PHYSICS_ITEM_V_MAX ? -PHYSICS_ITEM_V_MAX : (*mario_h_velocity - PHYSICS_ITEM_A);
			else
				*mario_h_velocity = (*mario_h_velocity - PHYSICS_A) < -PHYSICS_V_MAX ? -PHYSICS_V_MAX : (*mario_h_velocity - PHYSICS_A);
		}
		//�O�_�氱
		if ((*mario_press_right && *mario_h_velocity < 0) || (*mario_press_left && *mario_h_velocity > 0))
			*mario_stop = true;
		//�_�B�p�k�s
		if (!*mario_h_velocity)
			*mario_move_count = 8;
		//�_��ϦV�մ���V��
		if (mario_mushroom_status)
		{
			*mario_press_left = !*mario_press_left;
			*mario_press_right = !*mario_press_right;
		}
	}
	else
	{//���k�ҫ��άҩ�
		//�ͦV����
		if (*mario_h_velocity)
		{
			if (*mario_h_velocity > 0)
				*mario_h_velocity -= PHYSICS_RISIST_A;
			else
				*mario_h_velocity += PHYSICS_RISIST_A;
			if (!*mario_h_velocity)
				*mario_move_count = 8;
		}
	}


	//�ʧ@�P�_
	if (*mario_falling || *mario_stop)
		;//���ʧ@�A�w�T�w�H���ʧ@
	else if (!*mario_h_velocity)
	{//�R��
		*mario_stand = true;
	}
	else if (!*mario_falling && !*mario_stop)
	{//����
		if (*mario_h_velocity == PHYSICS_V_MAX || *mario_h_velocity == -PHYSICS_V_MAX)
		{//�̰��t
			//�_�B����4�����Ʈɤ����ʧ@
			if (!(*mario_move_count & 3))
				*mario_stand = !*mario_stand;
		}
		else
		{//���F�̰��t
			//�_�B����8�����Ʈɤ����ʧ@
			if (!(*mario_move_count & 7))
				*mario_stand = !*mario_stand;
		}
	}
	//�_�B��
	if (*mario_move_count & 16)
		*mario_move_count = *mario_move_count >> 1;
	(*mario_move_count)++;
	
	//////////////////////////////////////////////////////////
	//			  _     _    _ _____ _____ _____ 
	//			 | |   | |  | |_   _/ ____|_   _|
	//			 | |   | |  | | | || |  __  | |  
	//			 | |   | |  | | | || | |_ | | |  
	//			 | |___| |__| |_| || |__| |_| |_ 
	//			 |______\____/|_____\_____|_____|
	//////////////////////////////////////////////////////////
	if (pictureBox_luigi->Enabled)
	{
		//�����t��
		if (*luigi_falling)
		{//�b�Ť�
			if (*luigi_v_velocity < 0)
			{//���D��
				*luigi_v_velocity += PHYSICS_G;
			}
			else
			{//���U��
				//�ĪG�����I
				luigi_rolling_status = false;
				luigi_mushroom_status = false;

				//�ˬd�Ǫ��u��
				x = this->pictureBox_monster->Left - this->pictureBox_luigi->Left;
				y = this->pictureBox_monster->Top - this->pictureBox_luigi->Top - this->pictureBox_luigi->Height;
				if (this->pictureBox_monster->Enabled && x<48 && x>(-this->pictureBox_monster->Width) && y <= *luigi_v_velocity + PHYSICS_G && y >= 0)
				{
					if (*setting_sound)
						stamp_sound->Play();
					*monster_death_count = 5;
					//Jump
					*luigi_v_velocity = -18;
					this->pictureBox_luigi->Top = this->pictureBox_monster->Top - this->pictureBox_luigi->Height - 2;
					*luigi_falling = true;
					*luigi_current_platform = -1;
				}
				else
				{
					//�ˬd�U���x
					for (i = 0; i < platform_list->Length; i++)
					{
						if (platform_list[i]->Enabled)
						{
							//�ˬd�p�G�~�򱼷|���|���a
							x = platform_list[i]->Location.X - this->pictureBox_luigi->Location.X;
							y = platform_list[i]->Location.Y - 48;
							if (x > -183 && x < 38 && y >= this->pictureBox_luigi->Location.Y && y <= this->pictureBox_luigi->Location.Y + *luigi_v_velocity + PHYSICS_G)
							{//�|���a
								*luigi_falling = false;
								*luigi_v_velocity = 0;
								//�������ʨ쥭�x�W
								this->pictureBox_luigi->Top = platform_list[i]->Location.Y - 48;
								*luigi_current_platform = i;
								//����
								if (*setting_sound)
									fall_down_sound->Play();
								//�d�ݥثe���x����
								switch (platform_kind[i])
								{
								case 1:
									//�u��
									*luigi_v_velocity -= 18;
									this->pictureBox_luigi->Top -= 2;
									*luigi_falling = true;
									*luigi_current_platform = -1;
									*luigi_effect_platform = i;
									*luigi_effect_count = 8;
									//����
									if (*setting_sound)
										spring_platform_sound->Play();
									break;
								case 2:
									//�Ť�
									platform_list[i]->Enabled = false;
									*luigi_falling = true;
									*luigi_current_platform = -1;
									break;
								case 3:
									//�V���u��
									luigi_rolling_status = true;
									luigi_rolling_right = false;
									break;
								case 4:
									//�V�k�u��
									luigi_rolling_status = true;
									luigi_rolling_right = true;
									break;
								case 5:
									//�y��
									touch_spike(false, true, false);
									break;
								case 6:
									//�ϦV
									luigi_mushroom_status = true;
									break;
								}
								if (*luigi_hp < 10)
								{
									*luigi_hp += 1;
									this->pictureBox_2p_health->Image = luigi_health_image[*luigi_hp];
								}
								break;
							}
						}
					}
				}
				if (*luigi_falling)
				{//���|���a
					*luigi_v_velocity += PHYSICS_G;
				}
			}
		}
		else
		{//�b���x�W
			//�ˬd�O�_�٦b���x�W
			x = platform_list[*luigi_current_platform]->Location.X - this->pictureBox_luigi->Location.X;
			y = platform_list[*luigi_current_platform]->Location.Y - this->pictureBox_luigi->Location.Y;
			if (!(x > -183 && x < 38 && y > 16 && y <= 48))
			{//���}���x
				//���ˬd��U�A���ˬd��Tick���ʫ�
				//�۷��O�W��Tick���X���x�~�A�b��Tick�~���U
				*luigi_falling = true;
				*luigi_v_velocity += PHYSICS_G;
			}
		}

		//�����t��
		*luigi_stop = false;
		if (*luigi_press_left ^ *luigi_press_right)
		{//���k�Ȥ@���U
			//�Y�b�ϦV���x�h�մ���V��
			if (luigi_mushroom_status)
			{
				*luigi_press_left = !*luigi_press_left;
				*luigi_press_right = !*luigi_press_right;
			}
			//�T�{��V
			*luigi_turn_right = *luigi_press_right;
			//�p��t�� 
			if (*luigi_press_right)
			{
				if (*luigi_speedup)
					*luigi_h_velocity = (*luigi_h_velocity + PHYSICS_ITEM_A) > PHYSICS_ITEM_V_MAX ? PHYSICS_ITEM_V_MAX : (*luigi_h_velocity + PHYSICS_ITEM_A);
				else
					*luigi_h_velocity = (*luigi_h_velocity + PHYSICS_A) > PHYSICS_V_MAX ? PHYSICS_V_MAX : (*luigi_h_velocity + PHYSICS_A);
			}
			else
			{
				if (*luigi_speedup)
					*luigi_h_velocity = (*luigi_h_velocity - PHYSICS_ITEM_A) < -PHYSICS_ITEM_V_MAX ? -PHYSICS_ITEM_V_MAX : (*luigi_h_velocity - PHYSICS_ITEM_A);
				else
					*luigi_h_velocity = (*luigi_h_velocity - PHYSICS_A) < -PHYSICS_V_MAX ? -PHYSICS_V_MAX : (*luigi_h_velocity - PHYSICS_A);
			}
			//�O�_�氱
			if ((*luigi_press_right && *luigi_h_velocity < 0) || (*luigi_press_left && *luigi_h_velocity > 0))
				*luigi_stop = true;
			//�_�B�p�k�s
			if (!*luigi_h_velocity)
				*luigi_move_count = 8;
			//�_��ϦV�մ���V��
			if (luigi_mushroom_status)
			{
				*luigi_press_left = !*luigi_press_left;
				*luigi_press_right = !*luigi_press_right;
			}
		}
		else
		{//���k�ҫ��άҩ�
			//�ͦV����
			if (*luigi_h_velocity)
			{
				if (*luigi_h_velocity > 0)
					*luigi_h_velocity -= PHYSICS_RISIST_A;
				else
					*luigi_h_velocity += PHYSICS_RISIST_A;
				if (!*luigi_h_velocity)
					*luigi_move_count = 8;
			}
		}


		//�ʧ@�P�_
		if (*luigi_falling || *luigi_stop)
			;//���ʧ@�A�w�T�w�H���ʧ@
		else if (!*luigi_h_velocity)
		{//�R��
			*luigi_stand = true;
		}
		else if (!*luigi_falling && !*luigi_stop)
		{//����
			if (*luigi_h_velocity == PHYSICS_V_MAX || *luigi_h_velocity == -PHYSICS_V_MAX)
			{//�̰��t
				//�_�B����4�����Ʈɤ����ʧ@
				if (!(*luigi_move_count & 3))
					*luigi_stand = !*luigi_stand;
			}
			else
			{//���F�̰��t
				//�_�B����8�����Ʈɤ����ʧ@
				if (!(*luigi_move_count & 7))
					*luigi_stand = !*luigi_stand;
			}
		}
		//�_�B��
		if (*luigi_move_count & 16)
			*luigi_move_count = *luigi_move_count >> 1;
		(*luigi_move_count)++;
	}

	//////////////////////////////////////////////////////////
	//			  __  __                
	//			 |  \/  |               
	//			 | \  / | _____   _____ 
	//			 | |\/| |/ _ \ \ / / _ \
	//			 | |  | | (_) \ V /  __/
	//			 |_|  |_|\___/ \_/ \___|
	//////////////////////////////////////////////////////////
	//���x�W��
	if (!*time_freeze)
	{
		for (i = 0; i < platform_list->Length; i++)
		{
			if (platform_list[i]->Enabled)
			{
				platform_list[i]->Top -= *background_speed;
				if (platform_list[i]->Location.Y < this->status->Height - platform_list[i]->Height)
					platform_list[i]->Enabled = false;
			}
		}
	}
	//�S�Ĥ��
	if (*mario_effect_count)
	{
		pictureBox_mario_effect->Top = platform_list[*mario_effect_platform]->Location.Y - 26;
		if (*mario_effect_count == 8)
			pictureBox_mario_effect->Left = pictureBox_mario->Location.X - 16;
	}
	if (*luigi_effect_count)
	{
		pictureBox_luigi_effect->Top = platform_list[*luigi_effect_platform]->Location.Y - 26;
		if (*luigi_effect_count == 8)
			pictureBox_luigi_effect->Left = pictureBox_luigi->Location.X - 16;
	}

	//�D��W��
	if (this->pictureBox_item->Enabled && !*time_freeze)
	{
		this->pictureBox_item->Top -= *background_speed;
		if (this->pictureBox_item->Location.Y < this->status->Height)
			this->pictureBox_item->Enabled = false;
	}

	//�Ǫ�
	if (this->pictureBox_monster->Enabled && !*time_freeze)
	{
		//�W��
		this->pictureBox_monster->Top -= *background_speed;
		if (this->pictureBox_monster->Location.Y < this->status->Height - this->pictureBox_monster->Height)
			this->pictureBox_monster->Enabled = false;

		//����
		if (!*monster_kind)
		{//turtle bump
			if (*monster_target)
			{//���ؼ�
				if (*monster_target == 1)
				{//mario
					//���V�ؼ�
					*monster_turn_right = (this->pictureBox_mario->Location.X + 24 > this->pictureBox_monster->Location.X + 16);
					if (*mario_current_platform == *monster_current_platform)
					{//move 5
						x = this->pictureBox_monster->Location.X - platform_list[*monster_current_platform]->Location.X + (*monster_turn_right ? 6 : -6);
						//����ˬd
						if (x > -6 && x < 166)
						{//�~��
							this->pictureBox_monster->Left = this->pictureBox_monster->Location.X + (*monster_turn_right ? 6 : -6);
						}
						else
						{//��V
							*monster_turn_right = !*monster_turn_right;
						}
					}
					else
					{//move 3
						x = this->pictureBox_monster->Location.X - platform_list[*monster_current_platform]->Location.X + (*monster_turn_right ? 3 : -3);
						//����ˬd
						if (x > 0 && x < 160)
						{//�~��
							this->pictureBox_monster->Left = this->pictureBox_monster->Location.X + (*monster_turn_right ? 3 : -3);
						}
					}
				}
				else
				{//luigi
				 //���V�ؼ�
					*monster_turn_right = (this->pictureBox_luigi->Location.X + 24 > this->pictureBox_monster->Location.X + 16);
					if (*luigi_current_platform == *monster_current_platform)
					{//move 5
						x = this->pictureBox_monster->Location.X - platform_list[*monster_current_platform]->Location.X + (*monster_turn_right ? 6 : -6);
						//����ˬd
						if (x > -6 && x < 166)
						{//�~��
							this->pictureBox_monster->Left = this->pictureBox_monster->Location.X + (*monster_turn_right ? 3 : -3);
						}
						else
						{//��V
							*monster_turn_right = !*monster_turn_right;
						}
					}
					else
					{//move 3
						x = this->pictureBox_monster->Location.X - platform_list[*monster_current_platform]->Location.X + (*monster_turn_right ? 3 : -3);
						//����ˬd
						if (x > 0 && x < 160)
						{//�~��
							this->pictureBox_monster->Left = this->pictureBox_monster->Location.X + (*monster_turn_right ? 3 : -3);
						}
					}
				}
			}
			else
			{//��ؼ�
				if (*mario_current_platform == *monster_current_platform)
					*monster_target = 1;
				else if (pictureBox_luigi->Enabled && *luigi_current_platform == *monster_current_platform)
					*monster_target = 2;
				else
				{//�L�ؼ�
					x = this->pictureBox_monster->Location.X - platform_list[*monster_current_platform]->Location.X + (*monster_turn_right ? 3 : -3);
					//����ˬd
					if (x > 0 && x < 160)
					{//�~��
						this->pictureBox_monster->Left = this->pictureBox_monster->Location.X + (*monster_turn_right ? 3 : -3);
					}
					else
					{//��V
						*monster_turn_right = !*monster_turn_right;
					}
				}
			}
		}
		else
		{//mush
			x = this->pictureBox_monster->Location.X - platform_list[*monster_current_platform]->Location.X + (*monster_turn_right ? 3 : -3);
			//����ˬd
			if (x > 0 && x < 160)
			{//�~��
				this->pictureBox_monster->Left = this->pictureBox_monster->Location.X + (*monster_turn_right ? 3 : -3);
			}
			else
			{//��V
				*monster_turn_right = !*monster_turn_right;
			}
		}
	}

	//�����ڲ���
	//����
	if (mario_rolling_status)
		x = this->pictureBox_mario->Location.X + *mario_h_velocity + (mario_rolling_right ? PHYSICS_WHEEL_SPEED : -PHYSICS_WHEEL_SPEED);
	else
		x = this->pictureBox_mario->Location.X + *mario_h_velocity;
	//����ˬd
	if (x < 0)
		this->pictureBox_mario->Left = 0;
	else if (x > 652)
		this->pictureBox_mario->Left = 652;
	else
		this->pictureBox_mario->Left = x;
	//����
	if (!*time_freeze)
		y = this->pictureBox_mario->Location.Y + *mario_v_velocity - *background_speed;
	else
		y = this->pictureBox_mario->Location.Y + *mario_v_velocity;
	if (y > this->Height)
	{//���쩳��
		if (*mario_invincible)
		{//�L��
			//�����쳻�ݨí��]�t��
			this->pictureBox_mario->Top = this->status->Height + this->pictureBox_spike->Height + 10;
			*mario_v_velocity = 3;
		}
		else
		{//�L��
			touch_spike(true, false, true);
		}
	}
	else if (y <= this->pictureBox_spike->Height + this->status->Height)
	{//�Y�����
		touch_spike(true, false, false);
	}
	else
		this->pictureBox_mario->Top = y;
	//�����N����
	if (pictureBox_luigi->Enabled)
	{
		//����
		if (luigi_rolling_status)
			x = this->pictureBox_luigi->Location.X + *luigi_h_velocity + (luigi_rolling_right ? PHYSICS_WHEEL_SPEED : -PHYSICS_WHEEL_SPEED);
		else
			x = this->pictureBox_luigi->Location.X + *luigi_h_velocity;
		//����ˬd
		if (x < 0)
			this->pictureBox_luigi->Left = 0;
		else if (x > 652)
			this->pictureBox_luigi->Left = 652;
		else
			this->pictureBox_luigi->Left = x;
		//����
		if (!*time_freeze)
			y = this->pictureBox_luigi->Location.Y + *luigi_v_velocity - *background_speed;
		else
			y = this->pictureBox_luigi->Location.Y + *luigi_v_velocity;
		if (y > this->Height)
		{//���쩳��
			if (*luigi_invincible)
			{//�L��
			 //�����쳻�ݨí��]�t��
				this->pictureBox_luigi->Top = this->status->Height + this->pictureBox_spike->Height + 10;
				*luigi_v_velocity = 3;
			}
			else
			{//�L��
				touch_spike(false, false, true);
			}
		}
		else if (y <= this->pictureBox_spike->Height + this->status->Height)
		{//�Y�����
			touch_spike(false, false, false);
		}
		else
			this->pictureBox_luigi->Top = y;
	}
	
	//////////////////////////////////////////////////////////
	//			  _____ _                    _____            _             _ 
	//			 |_   _| |                  / ____|          | |           | |
	//			   | | | |_ ___ _ __ ___   | |     ___  _ __ | |_ _ __ ___ | |
	//			   | | | __/ _ \ '_ ` _ \  | |    / _ \| '_ \| __| '__/ _ \| |
	//			  _| |_| ||  __/ | | | | | | |___| (_) | | | | |_| | | (_) | |
	//			 |_____|\__\___|_| |_| |_|  \_____\___/|_| |_|\__|_|  \___/|_|
	//////////////////////////////////////////////////////////
	//�D��Ҧ��B�D��s�b
	if (*setting_item && this->pictureBox_item->Enabled)
	{
		//mario
		if (!*mario_item)
		{
			x = this->pictureBox_item->Left - this->pictureBox_mario->Left;
			y = this->pictureBox_item->Top - this->pictureBox_mario->Top;
			if (x<48 && x>-32 && y<32 && y>-48)
			{
				//����
				if (*setting_sound)
					this->axWindowsMediaPlayer_sound_get_item->Ctlcontrols->play();
				*mario_item = *item_kind;
				this->pictureBox_1p_item->Image = itemcolumn_image[*item_kind];
				this->pictureBox_item->Enabled = false;
			}
		}
		//luigi
		if (pictureBox_luigi->Enabled && !*luigi_item)
		{
			x = this->pictureBox_item->Left - this->pictureBox_luigi->Left;
			y = this->pictureBox_item->Top - this->pictureBox_luigi->Top;
			if (x<48 && x>-32 && y<32 && y>-48)
			{
				//����
				if (*setting_sound)
					this->axWindowsMediaPlayer_sound_get_item->Ctlcontrols->play();
				*luigi_item = *item_kind;
				this->pictureBox_2p_item->Image = itemcolumn_image[*item_kind];
				this->pictureBox_item->Enabled = false;
			}
		}
	}

	//////////////////////////////////////////////////////////
	//			  __  __                 _                              _             _ 
	//			 |  \/  |               | |                            | |           | |
	//			 | \  / | ___  _ __  ___| |_ ___ _ __    ___ ___  _ __ | |_ _ __ ___ | |
	//			 | |\/| |/ _ \| '_ \/ __| __/ _ \ '__|  / __/ _ \| '_ \| __| '__/ _ \| |
	//			 | |  | | (_) | | | \__ \ ||  __/ |    | (_| (_) | | | | |_| | | (_) | |
	//			 |_|  |_|\___/|_| |_|___/\__\___|_|     \___\___/|_| |_|\__|_|  \___/|_|
	//////////////////////////////////////////////////////////
	//�Ǫ��ˬd
	if (*setting_item && this->pictureBox_monster->Enabled && !*monster_death_count)
	{
		//mario
		x = this->pictureBox_monster->Left - this->pictureBox_mario->Left;
		y = this->pictureBox_monster->Top - this->pictureBox_mario->Top;
		if (x<48 && x>-this->pictureBox_monster->Width && y<this->pictureBox_monster->Height && y>-48)
		{//bump
			if (*setting_sound)
				bump_sound->Play();
			if(this->pictureBox_mario->Left + 24  > this->pictureBox_monster->Left + 16)
				*mario_h_velocity = 18;
			else
				*mario_h_velocity = -18;
		}
		//luigi
		if (this->pictureBox_luigi->Enabled)
		{
			x = this->pictureBox_monster->Left - this->pictureBox_luigi->Left;
			y = this->pictureBox_monster->Top - this->pictureBox_luigi->Top;
			if (x<48 && x>-this->pictureBox_monster->Width && y<this->pictureBox_monster->Height && y>-48)
			{//bump
				if (*setting_sound)
					bump_sound->Play();
				if (this->pictureBox_luigi->Left + 24  > this->pictureBox_monster->Left + 16)
					*luigi_h_velocity = 18;
				else
					*luigi_h_velocity = -18;
			}
		}
	}

	//////////////////////////////////////////////////////////
	//			        _       _    __                                           _       
	//			       | |     | |  / _|                                         | |      
	//			  _ __ | | __ _| |_| |_ ___  _ __ _ __ ___     ___ _ __ ___  __ _| |_ ___ 
	//			 | '_ \| |/ _` | __|  _/ _ \| '__| '_ ` _ \   / __| '__/ _ \/ _` | __/ _ \
	//			 | |_) | | (_| | |_| || (_) | |  | | | | | | | (__| | |  __/ (_| | ||  __/
	//			 | .__/|_|\__,_|\__|_| \___/|_|  |_| |_| |_|  \___|_|  \___|\__,_|\__\___|
	//			 | |                                                                      
	//			 |_| 
	//////////////////////////////////////////////////////////
	
	//�a�O����
	if(!*time_freeze && !*platform_count)
	{
		new_platform = false;
		
		for (i = 0; i < platform_list->Length; i++)
		{
			if (!platform_list[i]->Enabled)
			{
				//�Ĥ@�� : �@�륭�x		�w��
				//�ĤG�� : �u�� �u��	���q
				//�ĤT�� : �ϦV			�x��
				//�ĥ|�� : �Ť� �y��	�s��X�{�Ӧh�L�k�ͦs


				prob = (rand() % 100);//0 ~ 99
				if (prob < platform_kind_prob[0])
				{//�Ĥ@��
					//�@��
					platform_list[i]->Image = platform_image[0];
					platform_kind[i] = 0;
				}
				else if ((prob -= platform_kind_prob[0]) < platform_kind_prob[1])
				{//�ĤG��
					prob = rand() % 3;
					switch (prob)
					{
					case 0://�u��
						platform_list[i]->Image = platform_image[1];
						platform_kind[i] = 1;
						break;
					case 1://�u�� ��
						platform_list[i]->Image = platform_image[3];
						platform_kind[i] = 3;
						break;
					case 2://�u�� �k
						platform_list[i]->Image = platform_image[4];
						platform_kind[i] = 4;
						break;
					}
				}
				else if ((prob -= platform_kind_prob[1]) < platform_kind_prob[2])
				{//�ĤT��
					//�ϦV
					platform_list[i]->Image = platform_image[6];
					platform_kind[i] = 6;
				}
				else if ((prob -= platform_kind_prob[2]) < platform_kind_prob[3])
				{//�ĥ|��
					prob = rand() % 2;
					if (prob)
					{//�Ť�
						platform_list[i]->Image = platform_image[2];
						platform_kind[i] = 2;
					}
					else
					{//�y��
						platform_list[i]->Image = platform_image[5];
						platform_kind[i] = 5;
					}
				}
				platform_list[i]->Top = this->Height;
				platform_list[i]->Left = (rand() + platform_list[i]->Location.X) % 508;
				platform_list[i]->Enabled = true;

				//�͹D��
				if (*setting_item && !this->pictureBox_item->Enabled && platform_kind[i] != 1)
				{
					prob = (rand() % 50);
					if (prob < 2)
					{
						this->pictureBox_item->Enabled = true;
						this->pictureBox_item->Top = this->Height - this->pictureBox_item->Height;
						this->pictureBox_item->Left = platform_list[i]->Left + (rand() % (192 - this->pictureBox_item->Width));
						this->pictureBox_item->Image = item_image[prob * 2 + 2];
						*item_kind = prob * 2 + 2;
					}
				}

				//�ͩǪ�(�Ť� �u�����x���ͩ�)
				if (*setting_item && !this->pictureBox_monster->Enabled && platform_kind[i] != 2 && platform_kind[i] != 1)
				{
					prob = (rand() % 25);
					if (prob < 2)
					{
						if (prob)
						{//mush
							this->pictureBox_monster->Height = 32;
						}
						else
						{//turtle
							this->pictureBox_monster->Height = 54;
							*monster_target = 0;
						}
						*monster_kind = prob;
						this->pictureBox_monster->Enabled = true;
						this->pictureBox_monster->Top = this->Height - this->pictureBox_monster->Height;
						this->pictureBox_monster->Left = platform_list[i]->Left + (rand() % (192 - this->pictureBox_item->Width));
						*monster_move_count = 6;
						*monster_current_platform = i;
					}
				}

				new_platform = true;
				break;
			}
		}

		//���ͦa�O�~��s�a�O�p�ƾ�
		if (new_platform)
		{
			//�ͦa�O�W�v����
			switch (*background_speed)
			{
			case 3:
				*platform_count = 32;
				break;
			case 4:
				*platform_count = 25;
				break;
			case 5:
				*platform_count = 21;
				break;
			case 6:
				*platform_count = 19;
				break;
			case 7:
				*platform_count = 18;
				break;
			case 8:
				*platform_count = 17;
				break;
			case 9:
				*platform_count = 16;
				break;
			}
		}
	}
	this->Refresh();
	return;
}
public:  virtual void OnPaint(PaintEventArgs^ e) override {
	
	//�~�Ӱʧ@
	__super::OnPaint(e);

	////�ۭqø��
	////�ϼh���� : ���ݦy�� > �S�� > Buff > �D�� > �������H�� > ���x > ���x�W�H�� > �Ǫ�
	static int i;

	//�e�Ǫ�
	if (this->pictureBox_monster->Enabled)
	{//pictureBox_monster
		if (*monster_kind)
		{//mush
			if (*monster_death_count)
				e->Graphics->DrawImage(monster_image[2], this->pictureBox_monster->Location.X, this->pictureBox_monster->Location.Y, this->pictureBox_monster->Width, this->pictureBox_monster->Height);
			else
			{
				if (*monster_stand)
					e->Graphics->DrawImage(monster_image[0], this->pictureBox_monster->Location.X, this->pictureBox_monster->Location.Y, this->pictureBox_monster->Width, this->pictureBox_monster->Height);
				else
					e->Graphics->DrawImage(monster_image[1], this->pictureBox_monster->Location.X, this->pictureBox_monster->Location.Y, this->pictureBox_monster->Width, this->pictureBox_monster->Height);
			}
		}
		else
		{//turtle
			if (*monster_death_count)
				e->Graphics->DrawImage(monster_image[7], this->pictureBox_monster->Location.X, this->pictureBox_monster->Location.Y, this->pictureBox_monster->Width, this->pictureBox_monster->Height);
			else
			{
				if (*monster_stand)
					e->Graphics->DrawImage((*monster_turn_right ? monster_image[4] : monster_image[6]), this->pictureBox_monster->Location.X, this->pictureBox_monster->Location.Y, this->pictureBox_monster->Width, this->pictureBox_monster->Height);
				else
					e->Graphics->DrawImage((*monster_turn_right ? monster_image[3] : monster_image[5]), this->pictureBox_monster->Location.X, this->pictureBox_monster->Location.Y, this->pictureBox_monster->Width, this->pictureBox_monster->Height);
			}
		}

			
	}

	//�e�����N
	if (pictureBox_luigi->Enabled)
	{
		if (*luigi_falling)
		{//�������H�������L
			;
		}
		else if (*luigi_stop)
		{//stop
			e->Graphics->DrawImage((*luigi_turn_right ? luigi_image[3] : luigi_image[7]), pictureBox_luigi->Location.X, pictureBox_luigi->Location.Y, pictureBox_luigi->Width, pictureBox_luigi->Height);
		}
		else if (*luigi_stand)
		{//stand
			e->Graphics->DrawImage((*luigi_turn_right ? luigi_image[0] : luigi_image[4]), pictureBox_luigi->Location.X, pictureBox_luigi->Location.Y, pictureBox_luigi->Width, pictureBox_luigi->Height);
		}
		else
		{//walk
			e->Graphics->DrawImage((*luigi_turn_right ? luigi_image[1] : luigi_image[5]), pictureBox_luigi->Location.X, pictureBox_luigi->Location.Y, pictureBox_luigi->Width, pictureBox_luigi->Height);
		}
	}
	//�e������
	if (*mario_falling)
	{//�������H�������L
		;
	}
	else if (*mario_stop)
	{//stop
		e->Graphics->DrawImage((*mario_turn_right ? mario_image[3] : mario_image[7]), pictureBox_mario->Location.X, pictureBox_mario->Location.Y, pictureBox_mario->Width, pictureBox_mario->Height);
	}
	else if (*mario_stand)
	{//stand
		e->Graphics->DrawImage((*mario_turn_right ? mario_image[0] : mario_image[4]), pictureBox_mario->Location.X, pictureBox_mario->Location.Y, pictureBox_mario->Width, pictureBox_mario->Height);
	}
	else
	{//walk
		e->Graphics->DrawImage((*mario_turn_right ? mario_image[1] : mario_image[5]), pictureBox_mario->Location.X, pictureBox_mario->Location.Y, pictureBox_mario->Width, pictureBox_mario->Height);
	}

	//���x
	for (i = 0; i < platform_list->Length; i++)
	{
		if (platform_list[i]->Enabled)
		{
			if (platform_kind[i] == 5)
				e->Graphics->DrawImage(platform_image[platform_kind[i]], platform_list[i]->Location.X, platform_list[i]->Location.Y - 16, platform_list[i]->Width, platform_list[i]->Height + 16);
			else
				e->Graphics->DrawImage(platform_image[platform_kind[i]], platform_list[i]->Location.X, platform_list[i]->Location.Y, platform_list[i]->Width, platform_list[i]->Height);
		}
	}

	//�������H��
	if (pictureBox_luigi->Enabled && *luigi_falling)
	{//jump
		e->Graphics->DrawImage((*luigi_turn_right ? luigi_image[2] : luigi_image[6]), pictureBox_luigi->Location.X, pictureBox_luigi->Location.Y, pictureBox_luigi->Width, pictureBox_luigi->Height);
	}
	if (*mario_falling)
	{//jump
		e->Graphics->DrawImage((*mario_turn_right ? mario_image[2] : mario_image[6]), pictureBox_mario->Location.X, pictureBox_mario->Location.Y, pictureBox_mario->Width, pictureBox_mario->Height);
	}

	//�e�D��
	if (pictureBox_item->Enabled)
	{
		e->Graphics->DrawImage(item_image[*item_kind], pictureBox_item->Location.X, pictureBox_item->Location.Y, pictureBox_item->Width, pictureBox_item->Height);
	}

	//�ebuff���
	//�����N
	if (pictureBox_luigi->Enabled)
	{
		if (*luigi_invincible)
		{//�L��
			e->Graphics->DrawImage(buff_image[0], pictureBox_luigi->Location.X + 10, pictureBox_luigi->Location.Y - 11, 9, 9);
		}
		if (*luigi_speedup)
		{//�[�t
			e->Graphics->DrawImage(buff_image[1], pictureBox_luigi->Location.X + 22, pictureBox_luigi->Location.Y - 11, 9, 9);
		}
	}
	//������
	if (*mario_invincible)
	{//�L��
		e->Graphics->DrawImage(buff_image[0], pictureBox_mario->Location.X + 10, pictureBox_mario->Location.Y - 11, 9, 9);
	}
	if (*mario_speedup)
	{//�[�t
		e->Graphics->DrawImage(buff_image[1], pictureBox_mario->Location.X + 22, pictureBox_mario->Location.Y - 11, 9, 9);
	}

	//�e�S��
	//�����N
	if (pictureBox_luigi->Enabled && *luigi_effect_count)
	{
		e->Graphics->DrawImage(effect_image[(9 - *luigi_effect_count) / 3], pictureBox_luigi_effect->Location.X, pictureBox_luigi_effect->Location.Y, pictureBox_luigi_effect->Width, pictureBox_luigi_effect->Height);
	}
	//������
	if (*mario_effect_count)
	{
		e->Graphics->DrawImage(effect_image[(9 - *mario_effect_count) / 3], pictureBox_mario_effect->Location.X, pictureBox_mario_effect->Location.Y, pictureBox_mario_effect->Width, pictureBox_mario_effect->Height);
	}

	//�e���ݦy��
	e->Graphics->DrawImage(spike_image, pictureBox_spike->Location.X, pictureBox_spike->Location.Y, pictureBox_spike->Width, pictureBox_spike->Height);
	return;
}
};
}
