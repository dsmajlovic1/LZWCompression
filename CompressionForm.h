#pragma once

#include <fstream>
#include <stdio.h>
#include "resource.h"
#include "LZW_algorithm.h"
#include "CompressionViewForm.h"
//#include <iostream>

namespace LZW_interface
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Threading;

	delegate void StatusDelegate();

	delegate void EncodedDelegate(array<uint16_t>^ encodedArray);

	delegate void DecodedDelegate(array<char>^ decodedArray);
	
	public ref class CompressionForm : public System::Windows::Forms::Form
	{
	public:
		CompressionForm(void)
		{
			InitializeComponent();
			this->Icon = gcnew System::Drawing::Icon(L"logoEtf.ico");
		}

	protected:
		~CompressionForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	protected:

	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openConverterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;

	private: System::Windows::Forms::GroupBox^ compressGroupBox;
	private: System::Windows::Forms::GroupBox^ decompressGroupBox;
	private: System::Windows::Forms::Button^ compressInputButton;

	private: System::Windows::Forms::TextBox^ compressInputTextBox;
	private: System::Windows::Forms::Button^ decompressInputButton;


	private: System::Windows::Forms::TextBox^ decompressInputTextBox;
	private: System::Windows::Forms::StatusStrip^ statusStrip;

	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel;
	private: System::Windows::Forms::OpenFileDialog^ openCompressionFileDialog;
	private: System::Windows::Forms::OpenFileDialog^ openDecompressionFileDialog;
	private: System::Windows::Forms::GroupBox^ compressOptionsGroupBox;
	private: System::Windows::Forms::Label^ originalSizeLabel;
	private: System::Windows::Forms::TextBox^ compressionSizeTextBox;
	private: System::Windows::Forms::Button^ saveCompressionButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ originalSizeTextBox;
	private: System::Windows::Forms::Button^ compressButton;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TextBox^ decompressedSizeTextBox;
	private: System::Windows::Forms::Button^ saveDecompressedButton;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ compressedSizeTextBox;
	private: System::Windows::Forms::Button^ decompressButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ToolStripMenuItem^ instructionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ aboutTheProjectToolStripMenuItem;

	private: Stream^ inStream;
	private: Stream^ outStream;

	private: String^ inputOriginalText;
	private: array<uint16_t>^ encoded;

	private: array<Byte>^ inputCompressedText;
	private: array<char>^ decoded;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;

	private: LZW_interface::CompressionViewForm^ secondForm;


	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CompressionForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openConverterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->instructionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutTheProjectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compressGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->compressOptionsGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->compressionSizeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->saveCompressionButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->originalSizeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->compressButton = (gcnew System::Windows::Forms::Button());
			this->originalSizeLabel = (gcnew System::Windows::Forms::Label());
			this->compressInputButton = (gcnew System::Windows::Forms::Button());
			this->compressInputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->decompressGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->decompressedSizeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->saveDecompressedButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->compressedSizeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->decompressButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->decompressInputButton = (gcnew System::Windows::Forms::Button());
			this->decompressInputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->openCompressionFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openDecompressionFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip->SuspendLayout();
			this->compressGroupBox->SuspendLayout();
			this->compressOptionsGroupBox->SuspendLayout();
			this->decompressGroupBox->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(560, 30);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openConverterToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(78, 26);
			this->fileToolStripMenuItem->Text = L"Window";
			// 
			// openConverterToolStripMenuItem
			// 
			this->openConverterToolStripMenuItem->Name = L"openConverterToolStripMenuItem";
			this->openConverterToolStripMenuItem->Size = System::Drawing::Size(194, 26);
			this->openConverterToolStripMenuItem->Text = L"Open converter";
			this->openConverterToolStripMenuItem->Click += gcnew System::EventHandler(this, &CompressionForm::openConverterToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(194, 26);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &CompressionForm::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->instructionsToolStripMenuItem,
					this->aboutTheProjectToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(55, 26);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// instructionsToolStripMenuItem
			// 
			this->instructionsToolStripMenuItem->Name = L"instructionsToolStripMenuItem";
			this->instructionsToolStripMenuItem->Size = System::Drawing::Size(209, 26);
			this->instructionsToolStripMenuItem->Text = L"Instructions";
			this->instructionsToolStripMenuItem->Click += gcnew System::EventHandler(this, &CompressionForm::instructionsToolStripMenuItem_Click);
			// 
			// aboutTheProjectToolStripMenuItem
			// 
			this->aboutTheProjectToolStripMenuItem->Name = L"aboutTheProjectToolStripMenuItem";
			this->aboutTheProjectToolStripMenuItem->Size = System::Drawing::Size(209, 26);
			this->aboutTheProjectToolStripMenuItem->Text = L"About the project";
			this->aboutTheProjectToolStripMenuItem->Click += gcnew System::EventHandler(this, &CompressionForm::aboutTheProjectToolStripMenuItem_Click);
			// 
			// compressGroupBox
			// 
			this->compressGroupBox->Controls->Add(this->compressOptionsGroupBox);
			this->compressGroupBox->Controls->Add(this->compressInputButton);
			this->compressGroupBox->Controls->Add(this->compressInputTextBox);
			this->compressGroupBox->Location = System::Drawing::Point(13, 32);
			this->compressGroupBox->Name = L"compressGroupBox";
			this->compressGroupBox->Size = System::Drawing::Size(533, 175);
			this->compressGroupBox->TabIndex = 1;
			this->compressGroupBox->TabStop = false;
			this->compressGroupBox->Text = L"Compress";
			// 
			// compressOptionsGroupBox
			// 
			this->compressOptionsGroupBox->Controls->Add(this->label5);
			this->compressOptionsGroupBox->Controls->Add(this->label4);
			this->compressOptionsGroupBox->Controls->Add(this->compressionSizeTextBox);
			this->compressOptionsGroupBox->Controls->Add(this->saveCompressionButton);
			this->compressOptionsGroupBox->Controls->Add(this->label1);
			this->compressOptionsGroupBox->Controls->Add(this->originalSizeTextBox);
			this->compressOptionsGroupBox->Controls->Add(this->compressButton);
			this->compressOptionsGroupBox->Controls->Add(this->originalSizeLabel);
			this->compressOptionsGroupBox->Location = System::Drawing::Point(6, 60);
			this->compressOptionsGroupBox->Name = L"compressOptionsGroupBox";
			this->compressOptionsGroupBox->Size = System::Drawing::Size(521, 109);
			this->compressOptionsGroupBox->TabIndex = 2;
			this->compressOptionsGroupBox->TabStop = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(339, 68);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(42, 17);
			this->label5->TabIndex = 7;
			this->label5->Text = L"bytes";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(339, 18);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 17);
			this->label4->TabIndex = 6;
			this->label4->Text = L"bytes";
			// 
			// compressionSizeTextBox
			// 
			this->compressionSizeTextBox->Enabled = false;
			this->compressionSizeTextBox->Location = System::Drawing::Point(153, 65);
			this->compressionSizeTextBox->Name = L"compressionSizeTextBox";
			this->compressionSizeTextBox->Size = System::Drawing::Size(180, 22);
			this->compressionSizeTextBox->TabIndex = 5;
			this->compressionSizeTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// saveCompressionButton
			// 
			this->saveCompressionButton->Location = System::Drawing::Point(408, 67);
			this->saveCompressionButton->Name = L"saveCompressionButton";
			this->saveCompressionButton->Size = System::Drawing::Size(99, 23);
			this->saveCompressionButton->TabIndex = 4;
			this->saveCompressionButton->Text = L"Save";
			this->saveCompressionButton->UseVisualStyleBackColor = true;
			this->saveCompressionButton->Click += gcnew System::EventHandler(this, &CompressionForm::saveCompressionButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(11, 68);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(120, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Compressed size:";
			// 
			// originalSizeTextBox
			// 
			this->originalSizeTextBox->Enabled = false;
			this->originalSizeTextBox->Location = System::Drawing::Point(153, 15);
			this->originalSizeTextBox->Name = L"originalSizeTextBox";
			this->originalSizeTextBox->Size = System::Drawing::Size(180, 22);
			this->originalSizeTextBox->TabIndex = 2;
			this->originalSizeTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// compressButton
			// 
			this->compressButton->Location = System::Drawing::Point(408, 17);
			this->compressButton->Name = L"compressButton";
			this->compressButton->Size = System::Drawing::Size(99, 23);
			this->compressButton->TabIndex = 1;
			this->compressButton->Text = L"Compress";
			this->compressButton->UseVisualStyleBackColor = true;
			this->compressButton->Click += gcnew System::EventHandler(this, &CompressionForm::compressButton_Click);
			// 
			// originalSizeLabel
			// 
			this->originalSizeLabel->AutoSize = true;
			this->originalSizeLabel->Location = System::Drawing::Point(11, 20);
			this->originalSizeLabel->Name = L"originalSizeLabel";
			this->originalSizeLabel->Size = System::Drawing::Size(63, 17);
			this->originalSizeLabel->TabIndex = 0;
			this->originalSizeLabel->Text = L"File size:";
			// 
			// compressInputButton
			// 
			this->compressInputButton->Location = System::Drawing::Point(438, 31);
			this->compressInputButton->Name = L"compressInputButton";
			this->compressInputButton->Size = System::Drawing::Size(75, 23);
			this->compressInputButton->TabIndex = 1;
			this->compressInputButton->Text = L"Open file";
			this->compressInputButton->UseVisualStyleBackColor = true;
			this->compressInputButton->Click += gcnew System::EventHandler(this, &CompressionForm::compressInputButton_Click);
			// 
			// compressInputTextBox
			// 
			this->compressInputTextBox->Location = System::Drawing::Point(17, 31);
			this->compressInputTextBox->Name = L"compressInputTextBox";
			this->compressInputTextBox->Size = System::Drawing::Size(415, 22);
			this->compressInputTextBox->TabIndex = 0;
			// 
			// decompressGroupBox
			// 
			this->decompressGroupBox->Controls->Add(this->groupBox1);
			this->decompressGroupBox->Controls->Add(this->decompressInputButton);
			this->decompressGroupBox->Controls->Add(this->decompressInputTextBox);
			this->decompressGroupBox->Location = System::Drawing::Point(12, 213);
			this->decompressGroupBox->Name = L"decompressGroupBox";
			this->decompressGroupBox->Size = System::Drawing::Size(534, 176);
			this->decompressGroupBox->TabIndex = 2;
			this->decompressGroupBox->TabStop = false;
			this->decompressGroupBox->Text = L"Decompress";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->decompressedSizeTextBox);
			this->groupBox1->Controls->Add(this->saveDecompressedButton);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->compressedSizeTextBox);
			this->groupBox1->Controls->Add(this->decompressButton);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Location = System::Drawing::Point(7, 60);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(521, 109);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(339, 70);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(42, 17);
			this->label7->TabIndex = 9;
			this->label7->Text = L"bytes";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(339, 20);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(42, 17);
			this->label6->TabIndex = 8;
			this->label6->Text = L"bytes";
			// 
			// decompressedSizeTextBox
			// 
			this->decompressedSizeTextBox->Enabled = false;
			this->decompressedSizeTextBox->Location = System::Drawing::Point(153, 67);
			this->decompressedSizeTextBox->Name = L"decompressedSizeTextBox";
			this->decompressedSizeTextBox->Size = System::Drawing::Size(180, 22);
			this->decompressedSizeTextBox->TabIndex = 5;
			this->decompressedSizeTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// saveDecompressedButton
			// 
			this->saveDecompressedButton->Location = System::Drawing::Point(408, 66);
			this->saveDecompressedButton->Name = L"saveDecompressedButton";
			this->saveDecompressedButton->Size = System::Drawing::Size(99, 23);
			this->saveDecompressedButton->TabIndex = 4;
			this->saveDecompressedButton->Text = L"Save";
			this->saveDecompressedButton->UseVisualStyleBackColor = true;
			this->saveDecompressedButton->Click += gcnew System::EventHandler(this, &CompressionForm::saveDecompressedButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(11, 70);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(136, 17);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Decompressed size:";
			// 
			// compressedSizeTextBox
			// 
			this->compressedSizeTextBox->Enabled = false;
			this->compressedSizeTextBox->Location = System::Drawing::Point(153, 17);
			this->compressedSizeTextBox->Name = L"compressedSizeTextBox";
			this->compressedSizeTextBox->Size = System::Drawing::Size(180, 22);
			this->compressedSizeTextBox->TabIndex = 2;
			this->compressedSizeTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// decompressButton
			// 
			this->decompressButton->Location = System::Drawing::Point(408, 16);
			this->decompressButton->Name = L"decompressButton";
			this->decompressButton->Size = System::Drawing::Size(99, 23);
			this->decompressButton->TabIndex = 1;
			this->decompressButton->Text = L"Decompress";
			this->decompressButton->UseVisualStyleBackColor = true;
			this->decompressButton->Click += gcnew System::EventHandler(this, &CompressionForm::decompressButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(11, 22);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 17);
			this->label3->TabIndex = 0;
			this->label3->Text = L"File size:";
			// 
			// decompressInputButton
			// 
			this->decompressInputButton->Location = System::Drawing::Point(439, 31);
			this->decompressInputButton->Name = L"decompressInputButton";
			this->decompressInputButton->Size = System::Drawing::Size(75, 23);
			this->decompressInputButton->TabIndex = 3;
			this->decompressInputButton->Text = L"Open file";
			this->decompressInputButton->UseVisualStyleBackColor = true;
			this->decompressInputButton->Click += gcnew System::EventHandler(this, &CompressionForm::decompressInputButton_Click);
			// 
			// decompressInputTextBox
			// 
			this->decompressInputTextBox->Location = System::Drawing::Point(18, 32);
			this->decompressInputTextBox->Name = L"decompressInputTextBox";
			this->decompressInputTextBox->Size = System::Drawing::Size(415, 22);
			this->decompressInputTextBox->TabIndex = 2;
			// 
			// statusStrip
			// 
			this->statusStrip->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel });
			this->statusStrip->Location = System::Drawing::Point(0, 395);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(560, 26);
			this->statusStrip->TabIndex = 3;
			this->statusStrip->Text = L"statusStrip";
			// 
			// toolStripStatusLabel
			// 
			this->toolStripStatusLabel->Name = L"toolStripStatusLabel";
			this->toolStripStatusLabel->Size = System::Drawing::Size(52, 20);
			this->toolStripStatusLabel->Text = L"Status:";
			// 
			// openCompressionFileDialog
			// 
			this->openCompressionFileDialog->FileName = L"Select file...";
			this->openCompressionFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &CompressionForm::openCompressionFileDialog_FileOk);
			// 
			// openDecompressionFileDialog
			// 
			this->openDecompressionFileDialog->FileName = L"Select file...";
			this->openDecompressionFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &CompressionForm::openDecompressionFileDialog_FileOk);
			// 
			// CompressionForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(560, 421);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->decompressGroupBox);
			this->Controls->Add(this->compressGroupBox);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"CompressionForm";
			this->Text = L"LZW compressor";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->compressGroupBox->ResumeLayout(false);
			this->compressGroupBox->PerformLayout();
			this->compressOptionsGroupBox->ResumeLayout(false);
			this->compressOptionsGroupBox->PerformLayout();
			this->decompressGroupBox->ResumeLayout(false);
			this->decompressGroupBox->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	public: static array<uint16_t>^ convertPrimitiveUint16ToSystemArray(uint16_t* primitiveList, uint32_t size) {
		uint16_t* list = primitiveList;

		array<uint16_t>^ arrayList = gcnew array<uint16_t>(size);

		for (int i = 0; i < size; i++)
		{
			arrayList[i] = *list;
			list++;
		}
		return arrayList;
	}
	public: static array<char>^ convertPrimitiveCharToSystemArray(char* primitiveList, uint32_t size) {
		char* list = primitiveList;

		array<char>^ arrayList = gcnew array<char>(size);

		for (int i = 0; i < size; i++)
		{
			arrayList[i] = *list;
			list++;
		}

		return arrayList;
	}
	public: static array<uint8_t>^ convertUint16toUint8(array<uint16_t>^ array16)
	{
		array<uint8_t>^ array8 = gcnew array<uint8_t>(array16->Length * 2);

		for (int i = 0; i < array16->Length; i++)
		{
			array8[i * 2] = static_cast<uint8_t>(array16[i] >> 8);
			array8[i * 2 + 1] = static_cast<uint8_t>(array16[i]);
		}
		return array8;
	}

	private: static array<uint8_t>^ convertChartoUint8(array<char>^ arrayChar)
	{
		array<uint8_t>^ array8 = gcnew array<uint8_t>(arrayChar->Length);

		for (int i = 0; i < arrayChar->Length; i++)
		{
			array8[i] = static_cast<uint8_t>(arrayChar[i]);
		}
		return array8;
	}

	public: static char* convertStringToPrimitiveArray(String^ string) {
		char* charArray = new char[string->Length + 1];
		for (int i = 0; i < string->Length; i++)
		{
			charArray[i] = static_cast<char>(string[i]);
		}
		charArray[string->Length] = EOF;
		return charArray;
	}
	public: static uint16_t* convertByteArrayToPrimitiveUint16Array(array<Byte>^ arrayList) {
		uint16_t* byteArray = new uint16_t[(arrayList->Length + 2) / 2];

		for (int i = 0; i < arrayList->Length - 1; i++)
		{
			uint16_t twoBytes;
			if (i < arrayList->Length - 1) twoBytes = ((static_cast<uint16_t>(arrayList[i]) << 8) | static_cast<uint16_t>(arrayList[i + 1]));
			else twoBytes = static_cast<uint16_t>(arrayList[i]);

			i++;
			byteArray[(i + 1) / 2] = twoBytes;
		}

		return byteArray;
	}
	private: System::Void clearCompressionArea() {
		compressInputTextBox->Text = "";
		originalSizeTextBox->Text = "";
		compressionSizeTextBox->Text = "";
	}
	private: System::Void clearDecompressionArea() {
		decompressInputTextBox->Text = "";
		compressedSizeTextBox->Text = "";
		decompressedSizeTextBox->Text = "";
	}
	private: System::Void setCompressingStatus() {
		toolStripStatusLabel->Text = "Status: Compressing...";
	}
	private: System::Void setEncoded(array<uint16_t>^ encodedArray) {
		encoded = encodedArray;
		
		int size = encoded->Length * sizeof(encoded[0]); //16-bit integers
		compressionSizeTextBox->Text = size.ToString();

		toolStripStatusLabel->Text = "Status: Compressed";
	}

	private: System::Void setDecompressingStatus() {
		toolStripStatusLabel->Text = "Status: Decompressing...";
	}
	private: System::Void setDecoded(array<char>^ decodedArray) {
		decoded = decodedArray;

		int size = decoded->Length * sizeof(decoded[0]); //16-bit integers
		decompressedSizeTextBox->Text = size.ToString();

		toolStripStatusLabel->Text = "Status: Decompressed";
	}
	public: void compress(System::Object^ obj)
	{
		String ^ inputText = (String^)obj;

		StatusDelegate^ statusDelegate = gcnew StatusDelegate(this, &CompressionForm::setCompressingStatus);
		this->Invoke(statusDelegate);

		//Compress opened file
		char* primitive = CompressionForm::convertStringToPrimitiveArray(inputText);
		uint16_t* encodedArray;
		uint32_t encodedSize;

		encodedSize = lzw_compression::encodeLZW(primitive, inputText->Length, encodedArray);

		EncodedDelegate^ encodedDelegate = gcnew EncodedDelegate(this, &CompressionForm::setEncoded);
		this->Invoke(encodedDelegate, CompressionForm::convertPrimitiveUint16ToSystemArray(encodedArray, encodedSize));
		
		delete[] primitive;
		delete[] inputText;
		delete[] encodedArray;
	}
	public: void decompress(System::Object^ obj)
	{
		array<Byte>^ inputText = (array<Byte>^) obj;

		StatusDelegate^ statusDelegate = gcnew StatusDelegate(this, &CompressionForm::setDecompressingStatus);
		this->Invoke(statusDelegate);

		//Decompress opened file
		uint16_t* primitive = CompressionForm::convertByteArrayToPrimitiveUint16Array(inputText);
		char* decodedArray;
		uint32_t decodedSize;

		decodedSize = lzw_compression::decodeLZW(primitive, (inputText->Length + 2) / 2, decodedArray);
		
		DecodedDelegate^ decodedDelegate = gcnew DecodedDelegate(this, &CompressionForm::setDecoded);
		this->Invoke(decodedDelegate, CompressionForm::convertPrimitiveCharToSystemArray(decodedArray, decodedSize));

		//delete[] primitive;
		delete[] inputText;
		delete[] decodedArray;
	}
	private: System::Void compressInputButton_Click(System::Object^ sender, System::EventArgs^ e) {
		openCompressionFileDialog->FileName = "Select file...";
		openCompressionFileDialog->Title = "Open file for compression";
		openCompressionFileDialog->Filter = "Text files (*.txt)|*.txt";
		openCompressionFileDialog->Multiselect = false;
		openCompressionFileDialog->ShowDialog();
	}
	private: System::Void openCompressionFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		compressInputTextBox->Text = openCompressionFileDialog->FileName;

		//Read file information
		inputOriginalText = File::ReadAllText(openCompressionFileDialog->FileName);

		int size = inputOriginalText->Length+sizeof(inputOriginalText[0]);
		originalSizeTextBox->Text = size.ToString();
	}
	
	private: System::Void compressButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (inputOriginalText == nullptr)
		{
			toolStripStatusLabel->Text = "Status: File for compression not selected";
			return;
		}
		try 
		{
			Thread^ compressThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &CompressionForm::compress));
			compressThread->IsBackground = true;
			compressThread->Start(inputOriginalText);
		}
		catch (String^ s)
		{
			MessageBox::Show("Compression error!", "Exception", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		catch (Exception ^ e)
		{
			MessageBox::Show(e->Message, "Exception", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		
	}
	private: System::Void saveCompressionButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try
		{
			String^ path = compressInputTextBox->Text;

			//Save compressed file as new file
			path = path->Substring(0, path->Length - 4) + ".etf";

			if (File::Exists(path))
			{
				File::Delete(path);
			}
			outStream = File::OpenWrite(path);

			//convert array into writable array
			array<uint8_t>^ data = convertUint16toUint8(encoded);
			int size = encoded->Length * 2;
			outStream->Write(data, 0, data->Length); //encoded is uint16_t, data is twice as long
			outStream->Close();
			delete path;
			delete[] data;
			delete[] encoded;
			toolStripStatusLabel->Text = "Status: Saved";
			clearCompressionArea();
		}
		catch (Exception ^ e)
		{
			MessageBox::Show("File could not be saved!\n"+e->Message, "Exception", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	private: System::Void decompressInputButton_Click(System::Object^ sender, System::EventArgs^ e) {
		openDecompressionFileDialog->FileName = "Select file...";
		openDecompressionFileDialog->Title = "Open file for decompression";
		openDecompressionFileDialog->Multiselect = false;
		openDecompressionFileDialog->ShowDialog();
	}
	private: System::Void openDecompressionFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		if (openDecompressionFileDialog->FileName->Substring(openDecompressionFileDialog->FileName->Length - 4) == ".etf")
		{
			decompressInputTextBox->Text = openDecompressionFileDialog->FileName;

			//Read file information
			inputCompressedText = File::ReadAllBytes(openDecompressionFileDialog->FileName);

			int size = inputCompressedText->Length + sizeof(inputCompressedText[0]);
			compressedSizeTextBox->Text = size.ToString();
		}
		else
		{
			MessageBox::Show("The selected file did not have the right extension. \".etf\"extension is needed.", "Extension error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		
	}
	private: System::Void decompressButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (inputCompressedText == nullptr)
		{
			toolStripStatusLabel->Text = "Status: File for decompression not selected";
			return;
		}

		try
		{
			Thread^ decompressThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &CompressionForm::decompress));
			decompressThread->IsBackground = true;
			decompressThread->Start(inputCompressedText);
		}
		catch (String^ s)
		{
			MessageBox::Show("Decompression error!", "Exception", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		catch (Exception ^ e)
		{
			MessageBox::Show(e->Message, "Exception", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		
	}
	private: System::Void saveDecompressedButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try
		{
			//Save decompressed file
			String^ path = decompressInputTextBox->Text;
			path = path->Substring(0, path->Length - 4) + "-Decompressed.txt";
			if (File::Exists(path))
			{
				File::Delete(path);
			}
			outStream = File::OpenWrite(path);

			//convert array into writable array
			array<uint8_t>^ data = convertChartoUint8(decoded);
			outStream->Write(data, 0, data->Length);
			outStream->Close();
			delete path;
			delete[] data;
			delete[] decoded;
			toolStripStatusLabel->Text = "Status: Saved";
			clearDecompressionArea();
		}
		catch (Exception^ e)
		{
			MessageBox::Show("File could not be saved!\n"+e->Message, "Exception", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void openConverterToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		secondForm = gcnew LZW_interface::CompressionViewForm();
		secondForm->Show();
	}
private: System::Void aboutTheProjectToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("This application is a part of bachelor thesis at University of Sarajevo and it serves as an example of dictionary-based algorithm implementation.", "About this project", MessageBoxButtons::OK);
}
private: System::Void instructionsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("The file for compression should be in simple, \".txt\" format because that format is the one that decompressor puts out.\n\n The file for decompression should be of the \".etf\" format that this application outputs.", "How to use the application", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
};
}
