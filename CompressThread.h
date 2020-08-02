ref class CompressThread
{
private: String^ compressText;
public:
	CompressThread(String^ _compressText)
	{
		compressText = _compressText;
	}
	void compress()
	{
		//Compress opened file
		char* primitive = convertStringToPrimitiveArray(compressText);
		uint16_t* encodedArray;
		uint32_t encodedSize;

		encodedSize = lzw_compression::encodeLZW(primitive, compressText->Length, encodedArray);

		//lzw_compression::ThreadCall threadCall = new lzw_compression::ThreadCall();
		//CompressCall^ compressCall = gcnew CompressCall(primitive, inputOriginalText->Length, encodedArray, encodedSize);
		//Thread^ compressThread = gcnew Thread(gcnew ThreadStart(compressCall, &CompressCall::compress));
		//compressThread->Start();

		encoded = convertPrimitiveUint16ToSystemArray(encodedArray, encodedSize);

		int size = encoded->Length * sizeof(encoded[0]); //16-bit integers
		//int size = sizeof(encoded);

		compressionSizeTextBox->Text = size.ToString();
		toolStripStatusLabel->Text = "Status: Compressed";
		delete[] primitive;
		delete[] inputOriginalText;
		delete[] encodedArray;
	}
};
