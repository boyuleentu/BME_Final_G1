import google.generativeai as genai
import serial
import time

arduino_port = "COM3"
baud_rate = 1200

strings = ""

problem = "Help me break the following series of letters into correct sentences and correct spelling errors. Don’t change the subject arbitrarily. Just give me the corrected answer and don't answer me."
rule = """Analyze the given text to identify the subject and the appropriate form of the "be" verb. Follow these rules:
1. If the subject is a pronoun, determine the most likely pronoun based on its length, structure, and context:
- Single-letter subjects are most likely "I".
- Only two or three letters and "i" appears without "t", it is most likely "I"
- Three to Five-letter subjects could be "he", "she", or "it", depending on the gender, singularity or spelling in the context.
- Subjects like "they" suggest a plural entity.
2. If the "be" verb appears in the text:
- If it contains "i" and "s", it is most likely "is".
- If it is associated with a plural subject, it is most likely "are".
- Match the verb form to the subject's grammatical number and person (singular/plural).

Examples:
- Input: "ci_likse_arpbbls."
- Output: "I like apples.".
- Input: "hse iaxs fat."
- Output: "He is fat.".
This is the input:
"""

prompt = problem + rule

def chat_with_gemini(message):
    try:
        api_key = 'Your_API_key'
        genai.configure(api_key = api_key)

        model = genai.GenerativeModel('gemini-1.5-flash')
        response = model.generate_content(message)
        return response.text
    except Exception as e:
        print(f"Unexpected error: {e}")
        return "An error occurred while generating a response."


if __name__ == '__main__':
    # 初始化串列通訊
    try:
        arduino = serial.Serial(arduino_port, baud_rate, timeout=1)
        print(f"Connected to Arduino on port {arduino_port}")
        print("---------------------------")
        print("---------------------------")

        while(True):
            if arduino.in_waiting:
                data_raw = arduino.readline()  # 讀取一行
                data = data_raw.decode()   # 用預設的UTF-8解碼
                print("before: ",data)
                string = chat_with_gemini(prompt+data) + '\n'
                print("after: ",string)
                print("---------------------------")
                print("---------------------------")
                strings += string

                arduino.write(string.encode())  # 傳送字串，附加換行符
            time.sleep(3)
    except KeyboardInterrupt:
        print("Program terminated by user.")
    finally:
        if 'arduino' in locals() and arduino.is_open:
            arduino.close()
            print("Serial port closed.")


