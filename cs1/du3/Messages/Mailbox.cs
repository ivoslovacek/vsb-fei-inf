namespace Messages
{
    public class Mailbox
    {
        public MessageQueue<string> Queue;
        public List<MessageSerializerBase> List = new List<MessageSerializerBase>();

        public Mailbox(MessageQueue<string> queue)
        {
            this.Queue = queue;
        }

        public void SendMessage<T>(MessageSerializer<T> serializer, T message) where T : IMessage, new()
        {
            Queue.Enqueue(serializer.Serialize(message));
        }

        public void RegisterSerializer(MessageSerializerBase obj)
        {
            this.List.Add(obj);
        }

        public bool TryReceive<T>(string serializedMessage, out T receivedMessage) where T : IMessage, new()
        {
            foreach (var serializer in this.List)
            {
                if (serializer is MessageSerializer<T> typedSerializer)
                {
                    try
                    {
                        receivedMessage = typedSerializer.Deserialize(serializedMessage);
                        return true;
                    }
                    catch (InvalidMessageException)
                    {
                    }
                }
            }

            receivedMessage = default(T);
            return false;
        }

    }
}
