using System;
using System.IO;
using System.Text;

namespace pgm_splitter_test
{
    class Program
    {

        static string ReadString(BinaryReader reader)
        {
            StringBuilder builder = new StringBuilder();

            while (true)
            {
                char temp = reader.ReadChar();
                if (temp == 10 || temp == 0)
                    break;
                builder.Append(temp);
            }

            return builder.ToString();
        }

        static void SaveToFile(byte[,] img, int sizeX, int sizeY, string filename)
        {
            StreamWriter writer = new StreamWriter(filename);

            writer.Write($"P2\n{sizeX} {sizeY}\n255\n");
            for (int y = 0; y < sizeY; y++)
            {
                StringBuilder temp = new StringBuilder();

                for (int x = 0; x < sizeX; x++)
                    temp.Append($"{(int)img[x,y]} ");

                writer.Write($"{temp.ToString()}\n");
            }

            writer.Close();
        }


        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("No File selected!");
                Console.WriteLine("\nEnd");
                Console.ReadLine();
                return;
                
            }

            Console.WriteLine($"Opening File: {args[0]}");

            Stream readStream = new FileStream(args[0], FileMode.Open);
            BinaryReader reader = new BinaryReader(readStream);

            string version = ReadString(reader);
            int sizeX, sizeY;
            {
                string[] sizes = ReadString(reader).Split(' ');
                sizeX = int.Parse(sizes[0]);
                sizeY = int.Parse(sizes[1]);
            }
            string num_Unimportant = ReadString(reader);


            Console.WriteLine($"Image:");
            Console.WriteLine($" - Type: {version}");
            Console.WriteLine($" - Size {sizeX} x {sizeY}");

            if (!version.Equals("P5"))
            {
                Console.WriteLine("-> Image Format not compatible!");
                Console.WriteLine("\nEnd");
                Console.ReadLine();
                return;
            }


            int splitX, splitY;
            {
                while (true)
                {
                    Console.WriteLine("Enter Split Size (width height) (like \"100 100\")");
                    try
                    {
                        string[] temp = Console.ReadLine().Split(' ');
                        splitX = int.Parse(temp[0]);
                        splitY = int.Parse(temp[1]);

                        if (sizeX % splitX == 0 && sizeY % splitY == 0)
                            break;
                        Console.WriteLine(" - Sizes dont match!");
                    }
                    catch
                    {
                        Console.WriteLine(" - Invalid Input!");
                    }
                }
            }

            Console.WriteLine($"Splitting {sizeX}x{sizeY} Image into {sizeX/splitX}x{sizeY/splitY} {splitX}x{splitY} images.");

            byte[,] img = new byte[sizeX, sizeY];

            for (int y = 0; y < sizeY; y++)
                for (int x = 0; x < sizeX; x++)
                    img[x, y] = reader.ReadByte();

            reader.Close();

            if (Directory.Exists("split"))
                System.IO.Directory.Delete("split", true);
            Directory.CreateDirectory("split");


            for (int y = 0; y < sizeY / splitY; y++)
                for (int x = 0; x < sizeX / splitX; x++)
                {
                    byte[,] temp = new byte[splitX, splitY];

                    for (int y1 = 0; y1 < splitY; y1++)
                        for (int x1 = 0; x1 < splitX; x1++)
                            temp[x1, y1] = img[x*splitX + x1, y * splitY + y1];

                    SaveToFile(temp, splitX, splitY, $"split\\split_{x}_{y}.pgm");
                }




            Console.WriteLine("\nDone.");
            Console.ReadLine();
        }
    }
}
