
namespace cv3
{
    class Parser
    {
        public enum ParseOptions
        {
            NONE,
            ALLOW_WHITESPACES,
            ALLOW_NEGATIVE_NUMBERS,
            IGNORE_INVALID_CHARACTERS
        }

        public static int ParseInt(string str)
        {
            int tmp = 0;

            foreach (char each in str)
            {
                if (each >= '0' && each <= '9')
                {
                    tmp *= 10;
                    tmp += each - '0';
                }
                else
                {
                    return -1;
                }
            }

            return tmp;
        }

        public static int? ParseIntOrNull(string str)
        {
            int tmp = 0;

            foreach (char each in str)
            {
                if (each >= '0' && each <= '9')
                {
                    tmp *= 10;
                    tmp += each - '0';
                }
                else
                {
                    return null;
                }
            }

            return tmp;
        }

        public static bool TryParseInt(string str, out int tmpOut)
        {
            int tmp = 0;
            tmpOut = 0;
            foreach (char each in str)
            {
                if (each >= '0' && each <= '9')
                {
                    tmp *= 10;
                    tmp += each - '0';
                }
                else
                {
                    return false;
                }
            }

            tmpOut = tmp;
            return true;
        }

        public static int ParseIntOption(string str, ParseOptions options)
        {
            switch (options)
            {
                case ParseOptions.NONE:
                    return ParseInt(str);

                case ParseOptions.ALLOW_WHITESPACES:
                    {
                        int tmp = 0;

                        foreach (char each in str)
                        {
                            if (each >= '0' && each <= '9')
                            {
                                tmp *= 10;
                                tmp += each - '0';
                            }
                        }

                        return tmp;
                    }

                case ParseOptions.ALLOW_NEGATIVE_NUMBERS:
                    {
                        int tmp = 0;
                        int negative = 1;
                        if (str[0] == '-')
                        {
                            negative = -1;
                        }


                        foreach (char each in str)
                        {
                            if (each >= '0' && each <= '9')
                            {
                                tmp *= 10;
                                tmp += each - '0';
                            }
                        }

                        return negative * tmp;
                    }

                case ParseOptions.IGNORE_INVALID_CHARACTERS:
                    {
                        int tmp = 0;

                        foreach (char each in str)
                        {
                            if (each >= '0' && each <= '9')
                            {
                                tmp *= 10;
                                tmp += each - '0';
                            }
                        }

                        return tmp;
                    }

                default:
                    return -1;
            }
        }
    }
}
