program_mode = 99
line = 0
list_var = []
var_value = []
var_type = []


def read_file(file_path):
    global line
    try:
        with open(file_path, 'r') as file:
            for line_file in file:
                # Proses setiap baris di sini
                parts = line_file.strip().split()  # Memisahkan baris berdasarkan spasi
                line += 1
                check_command(parts, len(parts))
    except FileNotFoundError:
        print(f"File {file_path} tidak ditemukan.")
    except Exception as e:
        print(f"Terjadi kesalahan: {e}")


def check_command(command, length):
    global list_var
    global var_value
    global line
    if command[0] == 'TANDON':
        if length >= 2:
            list_var.append(command[1])
        else:
            print("line-"+str(line)+ " VARIABELE OPO?")
            return True
        if length == 3:
            if command[2].isdigit():
                var_value.append(int(command[2]))  # Simpan sebagai integer jika angka
                var_type.append('int')
            else:
                var_value.append(command[2])  # Simpan sebagai string jika bukan angka
                var_type.append('str')
        else:
            var_value.append(0)
    elif command[0] == 'PUTIN':
        if command[1] in list_var:
            index = list_var.index(command[1])
            user_input = input()  # Ambil input pengguna
            if user_input.isdigit():
                var_value[index] = int(user_input)  # Simpan sebagai integer jika input angka
            else:
                var_value[index] = user_input  # Simpan sebagai string jika input bukan angka
        else:
            print("line-"+str(line)+ " GK ONOK " + command[1] + " NAK KENE!")
            return True
    elif command[0] == 'LITERASI':
        kalimat=''
        for item in command[1:]:
            if item in list_var:
                index = list_var.index(item)
                kalimat += (str(var_value[index])+" " ) # Konversi ke string sebelum mencetak
            else:
                kalimat += (str(item)+" ")
        print(kalimat)
    elif command[0] == 'NIGERUNDAYO':
        print("Program selesai")
        return True
    elif command[0] == 'MORB_0b':
        if command[1] in list_var:
            index = list_var.index(command[1])
            var_value[index] = str(bin(int(var_value[index]))[2:])
        else:
            print("line-"+str(line)+ " SING KATE MBOK MORB OPO???")
            return True
    elif command[0] == 'MORB_0x':
        if command[1] in list_var:
            index = list_var.index(command[1])
            var_value[index] = str(hex(int(var_value[index]))[2:])
        else:
            print("line-"+str(line)+ " SING KATE MBOK MORB OPO???")
            return True
    elif command[0] == 'MORB_0o':
        if command[1] in list_var:
            index = list_var.index(command[1])
            var_value[index] = str(oct(int(var_value[index]))[2:])
        else:
            print("line-"+str(line)+ " SING KATE MBOK MORB OPO???")
            return True
    else:
        print("line-"+str(line)+ " KON NULIS OPO SEH IKI " + command[0] + "???")       


def main():
    try:
        read_file("kode.xdd")
    except Exception as e:
        print(f"Terjadi kesalahan: {e}")


if __name__ == "__main__":
    main()
