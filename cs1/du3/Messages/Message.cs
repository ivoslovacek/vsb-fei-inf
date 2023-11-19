namespace Messages
{
    public interface IMessage
    {
        string Serialize();
        void Deserialize(string str);
        char GetMark();
    }

    public class InvalidMessageException : Exception
    {
        public InvalidMessageException()
        {

        }
    }

    public class Message : IMessage
    {
        public string Text;

        public Message()
        {
            this.Text = "";
        }

        public Message(string str)
        {
            this.Text = str;
        }

        public string Serialize()
        {
            return this.Text;
        }

        public void Deserialize(string str)
        {
            this.Text = str;
        }

        public char GetMark()
        {
            return 'T';
        }

    }

    public class EmailMessage : IMessage
    {
        public string Email;
        public string Text;

        public EmailMessage()
        {
            this.Text = "";
            this.Email = "";
        }

        public EmailMessage(string email, string text)
        {
            this.Text = text;
            this.Email = email;
        }

        public string Serialize()
        {
            return $"{this.Email}:{this.Text}";
        }

        public void Deserialize(string str)
        {
            string[] tmp = str.Split(':');
            this.Email = tmp[0];
            this.Text = tmp[1];
        }

        public char GetMark()
        {
            return 'E';
        }
    }

    public abstract class MessageSerializerBase
    {

    }

    public class MessageSerializer<T> : MessageSerializerBase where T : IMessage, new()
    {
        public IEncryption Encryption;

        public MessageSerializer(IEncryption obj)
        {
            this.Encryption = obj;
        }

        public string Serialize(T obj)
        {
            string tmp = obj.Serialize();

            tmp = Encryption.Encrypt(tmp);

            return $"{obj.GetMark()}{Encryption.GetMark()}{tmp}";
        }

        public T Deserialize(string str)
        {
            char[] chars = str.ToCharArray();
            T tmp = new T();

            if (tmp.GetMark() != chars[0])
            {
                throw new InvalidMessageException();
            }

            if (Encryption.GetMark() != chars[1])
            {
                throw new InvalidMessageException();
            }

            string subStr = new string(chars, 2, str.Length - 2);

            tmp.Deserialize(Encryption.Decrypt(subStr));

            return tmp;
        }
    }

    public class EmptyQueueException : Exception
    {
        public EmptyQueueException()
        {
        }
    }

    public class MessageQueue<T>
    {
        T[] Data = new T[0];

        public bool IsEmpty
        {
            get { return this.Data.Length == 0; }
        }

        public void Enqueue(T value)
        {
            T[] tmp = new T[this.Data.Length + 1];
            Array.Copy(this.Data, tmp, this.Data.Length);
            tmp[this.Data.Length] = value;
            this.Data = tmp;
        }

        public T Dequeue()
        {
            if (this.IsEmpty)
            {
                throw new EmptyQueueException();
            }

            T front = this.Data[0];
            T[] tmp = new T[this.Data.Length - 1];
            Array.Copy(this.Data, 1, tmp, 0, tmp.Length);
            this.Data = tmp;

            return front;
        }
    }
}
