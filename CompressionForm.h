#pragma once

#include <fstream>
#include <stdio.h>
#include "LZW_algorithm.h"
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
	using namespace System::Windows::Forms;

	public ref class CompressionForm : public System::Windows::Forms::Form
	{
	public:
		CompressionForm(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
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
	private: FileStream^ outStream;

	private: String^ inputOriginalText;
	private: array<uint16_t>^ encoded;
	//private: String^ outputCompressedText;

	private: array<Byte>^ inputCompressedText;
	private: array<char>^ decoded;
	//private: String^ outputDecompressedText;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;


	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openConverterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->instructionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutTheProjectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compressGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->compressOptionsGroupBox = (gcnew System::Windows::Forms::GroupBox());
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
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
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
			this->menuStrip->Size = System::Drawing::Size(560, 28);
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
			this->fileToolStripMenuItem->Size = System::Drawing::Size(78, 24);
			this->fileToolStripMenuItem->Text = L"Window";
			// 
			// openConverterToolStripMenuItem
			// 
			this->openConverterToolStripMenuItem->Name = L"openConverterToolStripMenuItem";
			this->openConverterToolStripMenuItem->Size = System::Drawing::Size(194, 26);
			this->openConverterToolStripMenuItem->Text = L"Open converter";
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
			this->helpToolStripMenuItem->Size = System::Drawing::Size(55, 24);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// instructionsToolStripMenuItem
			// 
			this->instructionsToolStripMenuItem->Name = L"instructionsToolStripMenuItem";
			this->instructionsToolStripMenuItem->Size = System::Drawing::Size(209, 26);
			this->instructionsToolStripMenuItem->Text = L"Instructions";
			// 
			// aboutTheProjectToolStripMenuItem
			// 
			this->aboutTheProjectToolStripMenuItem->Name = L"aboutTheProjectToolStripMenuItem";
			this->aboutTheProjectToolStripMenuItem->Size = System::Drawing::Size(209, 26);
			this->aboutTheProjectToolStripMenuItem->Text = L"About the project";
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
			// decompressedSizeTextBox
			// 
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
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(339, 68);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(42, 17);
			this->label5->TabIndex = 7;
			this->label5->Text = L"bytes";
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
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(339, 70);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(42, 17);
			this->label7->TabIndex = 9;
			this->label7->Text = L"bytes";
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
	private: array<uint16_t>^ convertPrimitiveUint16ToSystemArray(uint16_t* primitiveList) {
		uint16_t* list = primitiveList;
		int i = 0;
		int size = *list;
		list += 1;
		array<uint16_t>^ arrayList = gcnew array<uint16_t>(size);

		while (*list != EOF && i < size)
		{
			arrayList[i] = *list;
			list++;
			i++;
		}
		delete[] primitiveList;
		return arrayList;
	}
	private: array<char>^ convertPrimitiveCharToSystemArray(char* primitiveList) {
		char* list = primitiveList;
		int i = 0;
		//int size = *list;
		//list += 1;
		while (*list != static_cast<uint8_t>(-1))
		{
			i++;
			list++;
		}
		//int size = (inputCompressedText->Length - 2); 
		int size = i;
		i = 0;
		list = primitiveList;
		array<char>^ arrayList = gcnew array<char>(size);

		while (i < size)
		{
			arrayList[i] = *list;
			list++;
			i++;
		}
		delete[] primitiveList;
		return arrayList;
	}
	private: array<uint8_t>^ convertUint16toUint8(array<uint16_t>^ array16)
	{
		array<uint8_t>^ array8 = gcnew array<uint8_t>(array16->Length * 2);

		for (int i = 0; i < array16->Length; i++)
		{
			array8[i*2] = static_cast<uint8_t>(array16[i] >> 8);
			array8[i*2+1] = static_cast<uint8_t>(array16[i]);
		}
		return array8;
	}

	private: char* convertStringToPrimitiveArray(String^ string) {
		char* charArray = new char[string->Length+1];
		for (int i = 0; i < string->Length; i++) 
		{
			charArray[i] = static_cast<char>(string[i]);
		}
		charArray[string->Length] = EOF;
		return charArray;
	}
	private: uint16_t* convertByteArrayToPrimitiveUint16Array(array<Byte>^ arrayList) {
		uint16_t* byteArray = new uint16_t[arrayList->Length + 1];
		int size = (arrayList->Length - 2)/2;
		byteArray[0] = static_cast<uint16_t>(size);
		for (int i = 0; i < arrayList->Length-1; i++)
		{
			uint16_t twoBytes;
			if (i < arrayList->Length - 1) twoBytes = ((static_cast<uint16_t>(arrayList[i]) << 8) | static_cast<uint16_t>(arrayList[i+1]));
			else twoBytes = static_cast<uint16_t>(arrayList[i]);

			i++;
			byteArray[(i+1)/2] = twoBytes;
		}
		byteArray[arrayList->Length] = EOF;
		return byteArray;
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
		//int size = sizeof(inputOriginalText);
		originalSizeTextBox->Text = size.ToString();
	}
	private: System::Void compressButton_Click(System::Object^ sender, System::EventArgs^ e) {
		//Compress opened file
		char* primitive = convertStringToPrimitiveArray(inputOriginalText);
		encoded = convertPrimitiveUint16ToSystemArray(lzw_compression::encodeLZW(primitive));

		int size = encoded->Length*sizeof(encoded[0]); //16-bit integers
		//int size = sizeof(encoded);

		compressionSizeTextBox->Text = size.ToString();
		delete[] primitive;
	}
	private: System::Void saveCompressionButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ path = compressInputTextBox->Text;
		//Save compressed file as new file
		outStream = File::OpenWrite(path->Substring(0, path->Length-4)+".lzw");

		//outStream->Write(convertArrayListToByteArray(encoded), 0, encoded->Length);

		//array<uint8_t>^ data = reinterpret_cast<array<uint8_t>^>(encoded);
		array<uint8_t>^ data = convertUint16toUint8(encoded);
		int size = encoded->Length*2;
		outStream->Write(data, 0, size); //encoded is uint16_t, data is twice as long
		outStream->Close();
	}
	private: System::Void decompressInputButton_Click(System::Object^ sender, System::EventArgs^ e) {
		openCompressionFileDialog->FileName = "Select file...";
		openDecompressionFileDialog->Title = "Open file for decompression";
		openCompressionFileDialog->Multiselect = false;
		openDecompressionFileDialog->ShowDialog();
	}
	private: System::Void openDecompressionFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		decompressInputTextBox->Text = openDecompressionFileDialog->FileName;

		//Read file information
		inputCompressedText = File::ReadAllBytes(openDecompressionFileDialog->FileName);

		int size = inputCompressedText->Length + sizeof(inputCompressedText[0]);
		//int size = sizeof(inputCompressedText);
		compressedSizeTextBox->Text = size.ToString();
	}
	private: System::Void decompressButton_Click(System::Object^ sender, System::EventArgs^ e) {
		//Decompress opened file
		uint16_t* primitive = convertByteArrayToPrimitiveUint16Array(inputCompressedText);
		decoded = convertPrimitiveCharToSystemArray(lzw_compression::decodeLZW(primitive));

		int size = decoded->Length * sizeof(decoded[0]); //8-bit char
		//int size = sizeof(decoded);

		decompressedSizeTextBox->Text = size.ToString();
		delete[] primitive;
	}
	private: System::Void saveDecompressedButton_Click(System::Object^ sender, System::EventArgs^ e) {
		//Save decompressed file
		String^ path = decompressInputTextBox->Text;
		outStream = File::OpenWrite(path->Substring(0, path->Length - 4) + "-Decompressed.txt");

		//outStream->Write(convertArrayListToByteArray(decoded), 0, decoded->Length);

		array<uint8_t>^ data = reinterpret_cast<array<uint8_t>^>(decoded);
		outStream->Write(data, 0, decoded->Length);
		outStream->Close();
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
