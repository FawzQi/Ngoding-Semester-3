import tkinter as tk
from tkinter import scrolledtext

file_name = "kode.xdd"
index_input = -1
program_mode = 99
line = 0
list_var = []
var_value = []
var_type = []
list_input = []
output = ""


def read_file(file_path):
    global line
    global output
    try:
        with open(file_path, 'r') as file:
            for line_file in file:
                # Proses setiap baris di sini
                parts = line_file.strip().split()  # Memisahkan baris berdasarkan spasi
                line += 1
                check_command(parts, len(parts))
    except FileNotFoundError:
        output += f"File {file_path} tidak ditemukan.\n"
    except Exception as e:
        output += f"Terjadi kesalahan: {e}\n"


def check_command(command, length):
    if len(command) == 0:
       return 0 # Tidak ada perintah

    global list_var
    global var_value
    global line
    global output
    global list_input
    global index_input

    if command[0] == 'TANDON':
        if length >= 2:
            list_var.append(command[1])
        else:
            output += "line-" + str(line) + " VARIABELE OPO?\n"
            return True
        if length == 3:
            var_value.append(command[2])  # Simpan sebagai string jika bukan angka
        else:
            var_value.append(0)
    elif command[0] == '0d':
        if length >= 2:
            list_var.append(command[1])
            var_type.append('0d')
            var_value.append(0)
        else:
            output += "line-" + str(line) + " VARIABELE OPO?\n"
            return True
        if length == 3:
            if command[2].isdigit():
                var_value.append(int(command[2]))  # Simpan sebagai integer jika angka
                
            else:
                output += "line-" + str(line) + " BUKAN DESIMAL IKI?\n"
                return True
        else:
            var_value.append(int(0))
    elif command[0] == '0b':
        if length >= 2:
            list_var.append(command[1])
            var_type.append('0b')
            var_value.append(0)
        else:
            output += "line-" + str(line) + " VARIABELE OPO?\n"
            return True
        if length == 3:
            if command[2].isdigit():
                var_value.append(int(command[2], 2))
                
            else:
                output += "line-" + str(line) + " BUKAN BINER IKI?\n"
                return True
    elif command[0] == '0x':
        if length >= 2:
            list_var.append(command[1])
            var_type.append('0x')
            var_value.append(0)
        else:
            output += "line-" + str(line) + " VARIABELE OPO?\n"
            return True
        if length == 3:   
                var_value.append(int(command[2], 16))
                
           
    elif command[0] == '0o':
        if length >= 2:
            list_var.append(command[1])
            var_type.append('0o')
            var_value.append(0)
        else:
            output += "line-" + str(line) + " VARIABELE OPO?\n"
            return True
        if length == 3:
            if command[2].isdigit():
                var_value.append(command[2])
            else:
                output += "line-" + str(line) + " BUKAN OKTAL IKI?\n"
                return True
    elif command[0] == 'RIZZUP':
        if command[1] in list_var:
            index = list_var.index(command[1])
            index_input += 1
            if index_input < len(list_input):
               user_input = list_input[index_input]  # Ambil input pengguna

            if var_type[index] == '0d':
                var_value[index] = int(user_input)  # Simpan sebagai integer jika input angka
            elif var_type[index] == '0b':
                var_value[index] = int(user_input, 2)  # Simpan sebagai integer jika input angka
            elif var_type[index] == '0x':
                var_value[index] = int(user_input, 16)
            elif var_type[index] == '0o':
                var_value[index] = int(user_input, 8)
            else:
                var_value[index] = user_input  # Simpan sebagai string jika input bukan angka
            
            
        else:
            output += "line-" + str(line) + " GK ONOK " + command[1] + " NAK KENE!\n"
            return True
    elif command[0] == 'PREENT':
        kalimat = ''
        for item in command[1:]:
            if item in list_var:
                index = list_var.index(item)
                if var_type[index] == "0d":
                    kalimat += ((str(var_value[index]) )+" ")
                elif var_type[index] == "0b":
                    kalimat += ((bin(var_value[index])[2:] )+" ")
                elif var_type[index] == "0x":
                    kalimat += ((hex(var_value[index])[2:] )+" ")
                elif var_type[index] == "0o":
                    kalimat += ((oct(var_value[index])[2:] )+" ")
                else:
                    kalimat += (str(var_value[index]) ) +" " # Konversi ke string sebelum mencetak
            else:
                kalimat += (str(item))+" "
        output += kalimat+"\n"
    elif command[0] == 'NIGERUNDAYO':
        output += "Program selesai\n"
        return True
    elif command[0] == 'MORB_0b':
        if command[1] in list_var:
            index = list_var.index(command[1])
            var_type[index] = '0b'
        else:
            output += "line-" + str(line) + " SING KATE MBOK MORB OPO???"
            return True
    elif command[0] == 'MORB_0x':
        if command[1] in list_var:
            index = list_var.index(command[1])
            var_type[index] = '0x'
        else:
            output += "line-" + str(line) + " SING KATE MBOK MORB OPO???"
            return True
    elif command[0] == 'MORB_0o':
        if command[1] in list_var:
            index = list_var.index(command[1])
            var_type[index] = '0o'
        else:
            output += "line-" + str(line) + " SING KATE MBOK MORB OPO???"
            return True
    elif command[0] == 'MORB_0d':
        if command[1] in list_var:
            index = list_var.index(command[1])
            var_type[index] = '0d'
        else:
            output += "line-" + str(line) + " SING KATE MBOK MORB OPO???"
            return True
    else:
        output += "line-" + str(line) + " KON NULIS OPO SEH IKI " + command[0] + "???"

# Fungsi untuk membuka file
def open_file():
    global file_name
    
    file_path = path_entry.get() # Ambil path dari kotak input
    file_name=file_path
    if file_path:
        path_entry.delete(0, tk.END)  # Kosongkan kotak input path
        path_entry.insert(0, file_path)  # Masukkan path yang dipilih
        with open(file_path, "r") as file:
            code_text.delete(1.0, tk.END)  # Kosongkan kotak teks kode
            code_text.insert(tk.END, file.read())  # Masukkan isi file ke kotak teks


def compile_code():
    global output
    global file_name
    global list_input
    global index_input# Reset variabel global
    global line, list_var, var_value, var_type, program_mode
    line = 0
    list_var = []
    var_value = []
    line = 0
    list_var = []
    var_value = []
    var_type = []
    list_input = []
    list_input = input_text.get("1.0", tk.END).split()  # Ambil input dari kotak input
    index_input = -1
    output = ""
    # Ambil kode dari kotak input
    code = code_text.get("1.0", tk.END)

    # Simpan kode ke file sementara
    if file_name:
        with open(file_name, "w") as file:
            file.write(code)
    else :
        output = "File tidak ditemukan\nTolong pilih dan buka file terlebih dahulu\n"
        output_text.config(state=tk.NORMAL)  # Aktifkan sementara
        output_text.delete("1.0", tk.END)
        output_text.insert(tk.END, output)
        output_text.config(state=tk.DISABLED)  # Nonaktifkan lagi
        return
        # Hasil kompilasi
    try:
        if not file_name:
          read_file(code)
        else:
          read_file(file_name)
    except Exception as e:
        output = f"Terjadi kesalahan: {e}"

    # Tampilkan hasil kompilasi di kotak output (tidak bisa diedit)
    output_text.config(state=tk.NORMAL)  # Aktifkan sementara
    output_text.delete("1.0", tk.END)
    output_text.insert(tk.END, output)
    output_text.config(state=tk.DISABLED)  # Nonaktifkan lagi

root = tk.Tk()
root.title("Inter-Intepre-Intrepeter")

# Bagian input path file dan tombol open
path_frame = tk.Frame(root)
path_frame.pack(pady=5)

path_entry = tk.Entry(path_frame, width=40)
path_entry.pack(side=tk.LEFT, padx=5)

open_button = tk.Button(path_frame, text="Open", command=open_file)
open_button.pack(side=tk.LEFT, padx=5)

# Buat kotak teks untuk input kode
code_label = tk.Label(root, text="Code:")
code_label.pack(padx=0,pady=0)
code_text = scrolledtext.ScrolledText(root, width=50, height=15)
code_text.pack(padx=10, pady=10)


input_label = tk.Label(root, text="Input:")
input_label.pack(padx=0,pady=0)
input_text =  scrolledtext.ScrolledText(root, width=50, height=5)
input_text.pack(padx=10, pady=10)


#with open("kode.xdd", "r") as file:
#    code_text.insert(tk.END, file.read())

# Buat tombol Compile
compile_button = tk.Button(root, text="Compile", command=compile_code)
compile_button.pack(pady=5)

# Buat kotak teks untuk output (non-editable)
output_label = tk.Label(root, text="Output:")
output_label.pack(padx=0,pady=0)
output_text = scrolledtext.ScrolledText(root, width=50, height=10)
output_text.pack(padx=10, pady=10)
output_text.config(state=tk.DISABLED)  # Nonaktifkan edit

# Jalankan aplikasi
root.mainloop()
