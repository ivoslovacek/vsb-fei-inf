namespace Messages
{
    public interface IEncryption
    {
        string Encrypt(string str);
        string Decrypt(string str);
        char GetMark();
    }

    public class Rot13Encryption : IEncryption
    {
        public string Encrypt(string str)
        {
            char[] tmp = str.ToCharArray();

            for (int i = 0; i < str.Length; i++)
            {
                tmp[i] = Rot13(tmp[i]);
            }

            return new string(tmp);
        }

        public string Decrypt(string str)
        {
            char[] tmp = str.ToCharArray();

            for (int i = 0; i < str.Length; i++)
            {
                tmp[i] = Rot13(tmp[i]);
            }

            return new string(tmp);
        }

        public char GetMark()
        {
            return 'R';
        }

        private char Rot13(char letter)
        {
            if (letter >= 'A' && letter <= 'Z')
            {
                letter = (char)('A' + (letter - 'A' + 13) % 26);
            }
            else if (letter >= 'a' && letter <= 'z')
            {
                letter = (char)('a' + (letter - 'a' + 13) % 26);
            }
            return letter;
        }
    }

    public class PasswordBasedEncryption : IEncryption
    {
        public string password
        {
            get; set;
        }

        public PasswordBasedEncryption(string password)
        {
            if (password == null)
            {
                throw new InvalidPasswordException();
            }

            if (password.Length == 0)
            {
                throw new InvalidPasswordException();
            }

            this.password = password;
        }

        public string Encrypt(string str)
        {
            int passwordLength = password.Length;
            char[] result = new char[str.Length];

            for (int i = 0; i < str.Length; i++)
            {
                int code = str[i];
                int passwordCode = password[i % passwordLength];
                result[i] = (char)(code + passwordCode);
            }

            return new string(result);
        }

        public string Decrypt(string str)
        {
            int passwordLength = password.Length;
            char[] result = new char[str.Length];

            for (int i = 0; i < str.Length; i++)
            {
                int code = str[i];
                int passwordCode = password[i % passwordLength];
                code -= passwordCode;

                if (code < 0)
                {
                    throw new InvalidPasswordException("rozdíl číselných kódů znaků byl záporný", str, this.password);
                }
                result[i] = (char)code;
            }

            return new string(result);
        }


        public char GetMark()
        {
            return 'P';
        }
    }

    public class InvalidPasswordException : Exception
    {
        public string str { get; }
        public string password { get; }

        public InvalidPasswordException()
        {
            this.str = "";
            this.password = "";
        }

        public InvalidPasswordException(string exceptionText, string str, string password)
        {
            this.str = str;
            this.password = password;
        }
    }
}
