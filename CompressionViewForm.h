#pragma once

#include <string>
#include "LZW_algorithm.h"

namespace LZW_interface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class CompressionViewForm : public System::Windows::Forms::Form
	{
	public:
		CompressionViewForm()
		{
			InitializeComponent();
		}

	protected:
		~CompressionViewForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ compressRadioButton;
	protected:

	private: System::Windows::Forms::RadioButton^ decompressRadioButton;
	private: System::Windows::Forms::TextBox^ firstTextBox;

	private: System::Windows::Forms::Button^ convertButton;
	private: System::Windows::Forms::TextBox^ secondTextBox;
	private: System::Windows::Forms::TextBox^ openFileTextBox;
	private: System::Windows::Forms::Button^ openFileButton;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;


	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->compressRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->decompressRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->firstTextBox = (gcnew System::Windows::Forms::TextBox());
			this->convertButton = (gcnew System::Windows::Forms::Button());
			this->secondTextBox = (gcnew System::Windows::Forms::TextBox());
			this->openFileTextBox = (gcnew System::Windows::Forms::TextBox());
			this->openFileButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// compressRadioButton
			// 
			this->compressRadioButton->AutoSize = true;
			this->compressRadioButton->Location = System::Drawing::Point(12, 41);
			this->compressRadioButton->Name = L"compressRadioButton";
			this->compressRadioButton->Size = System::Drawing::Size(92, 21);
			this->compressRadioButton->TabIndex = 0;
			this->compressRadioButton->TabStop = true;
			this->compressRadioButton->Text = L"Compress";
			this->compressRadioButton->UseVisualStyleBackColor = true;
			// 
			// decompressRadioButton
			// 
			this->decompressRadioButton->AutoSize = true;
			this->decompressRadioButton->Location = System::Drawing::Point(110, 41);
			this->decompressRadioButton->Name = L"decompressRadioButton";
			this->decompressRadioButton->Size = System::Drawing::Size(108, 21);
			this->decompressRadioButton->TabIndex = 1;
			this->decompressRadioButton->TabStop = true;
			this->decompressRadioButton->Text = L"Decompress";
			this->decompressRadioButton->UseVisualStyleBackColor = true;
			// 
			// firstTextBox
			// 
			this->firstTextBox->Location = System::Drawing::Point(12, 71);
			this->firstTextBox->Multiline = true;
			this->firstTextBox->Name = L"firstTextBox";
			this->firstTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->firstTextBox->Size = System::Drawing::Size(453, 509);
			this->firstTextBox->TabIndex = 2;
			// 
			// convertButton
			// 
			this->convertButton->Location = System::Drawing::Point(474, 318);
			this->convertButton->Name = L"convertButton";
			this->convertButton->Size = System::Drawing::Size(75, 23);
			this->convertButton->TabIndex = 4;
			this->convertButton->Text = L">>";
			this->convertButton->UseVisualStyleBackColor = true;
			this->convertButton->Click += gcnew System::EventHandler(this, &CompressionViewForm::convertButton_Click);
			// 
			// secondTextBox
			// 
			this->secondTextBox->Location = System::Drawing::Point(557, 71);
			this->secondTextBox->Multiline = true;
			this->secondTextBox->Name = L"secondTextBox";
			this->secondTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->secondTextBox->Size = System::Drawing::Size(453, 509);
			this->secondTextBox->TabIndex = 5;
			// 
			// openFileTextBox
			// 
			this->openFileTextBox->Location = System::Drawing::Point(12, 13);
			this->openFileTextBox->Name = L"openFileTextBox";
			this->openFileTextBox->Size = System::Drawing::Size(372, 22);
			this->openFileTextBox->TabIndex = 6;
			// 
			// openFileButton
			// 
			this->openFileButton->Location = System::Drawing::Point(390, 12);
			this->openFileButton->Name = L"openFileButton";
			this->openFileButton->Size = System::Drawing::Size(75, 23);
			this->openFileButton->TabIndex = 7;
			this->openFileButton->Text = L"Open";
			this->openFileButton->UseVisualStyleBackColor = true;
			this->openFileButton->Click += gcnew System::EventHandler(this, &CompressionViewForm::openFileButton_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"Select a file...";
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &CompressionViewForm::openFileDialog_FileOk);
			// 
			// CompressionViewForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1022, 592);
			this->Controls->Add(this->openFileButton);
			this->Controls->Add(this->openFileTextBox);
			this->Controls->Add(this->secondTextBox);
			this->Controls->Add(this->convertButton);
			this->Controls->Add(this->firstTextBox);
			this->Controls->Add(this->decompressRadioButton);
			this->Controls->Add(this->compressRadioButton);
			this->Name = L"CompressionViewForm";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: String^ convertPrimitiveUint16ToString(uint16_t* primitive, uint32_t size) {
		if (size < 1) return "";
		String^ newString = gcnew String(primitive[0].ToString());

		for (uint32_t i = 1; i < size; i++)
		{
			newString = newString + " " + primitive[i].ToString();
		}
		return newString;
	}
	private: String^ convertPrimitiveCharToString(char* primitive, uint32_t size) {
		if (size < 1) return "";
		String^ newString = gcnew String(primitive);
		newString = newString->Substring(0, size);
		return newString;
	}
	private: String^ convertUCharArrayToString(array<unsigned char>^ charArray) {
		if (charArray->Length < 2) return "";
		String^ newString = gcnew String(charArray[0].ToString() + charArray[1].ToString());

		for (int i = 2; i < charArray->Length; i++)
		{
			uint16_t twoBytes = (static_cast<uint16_t>(charArray[i]) << 8) | static_cast<uint16_t>(charArray[i + 1]);
			newString = newString + " " + twoBytes.ToString();
			i++;
		}
		return newString;
	}
	public: char* convertStringToPrimitiveCharArray(String^ string) {
		char* charArray = new char[string->Length + 1];
		for (int i = 0; i < string->Length; i++)
		{
			charArray[i] = static_cast<char>(string[i]);
		}
		charArray[string->Length] = EOF;
		return charArray;
	}
	private: uint16_t* convertStringToPrimitiveUint16Array(String^ string) {
		array<String^>^ stringArray = string->Split(' ');
		int size = stringArray->Length;
		uint16_t* intArray = new uint16_t[size+1];
		for (int i = 0; i < stringArray->Length; i++)
		{
			intArray[i] = Convert::ToUInt16(stringArray[i]);
		}
		intArray[size] = EOF;
		return intArray;
	}
	
	private: System::Void openFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog->FileName = "Select a file...";
		openFileDialog->Title = "Select a file";
		openFileDialog->Multiselect = false;
		openFileDialog->ShowDialog();

	}

	private: System::Void openFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		openFileTextBox->Text = openFileDialog->FileName;
		if (openFileDialog->FileName->Substring(openFileDialog->FileName->Length-4) == ".etf") firstTextBox->Text = convertUCharArrayToString(File::ReadAllBytes(openFileDialog->FileName));
		else  firstTextBox->Text = File::ReadAllText(openFileDialog->FileName);
	}
	private: System::Void convertButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (compressRadioButton->Checked)
		{
			char* primitive = convertStringToPrimitiveCharArray(firstTextBox->Text);

			uint16_t* encodedArray;
			uint32_t encodedSize;

			encodedSize = lzw_compression::encodeLZW(primitive, firstTextBox->Text->Length, encodedArray);

			secondTextBox->Text = convertPrimitiveUint16ToString(encodedArray, encodedSize);
		}
		else if (decompressRadioButton->Checked)
		{
			uint32_t size = firstTextBox->Text->Split(' ')->Length;
			uint16_t* primitive = convertStringToPrimitiveUint16Array(firstTextBox->Text);

			char* decodedArray;
			uint32_t decodedSize;

			decodedSize = lzw_compression::decodeLZW(primitive, size, decodedArray);

			secondTextBox->Text = convertPrimitiveCharToString(decodedArray, decodedSize);
		}
		else
		{

		}
	}

};
}
