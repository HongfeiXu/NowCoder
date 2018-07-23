using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingInterviewsCSharp
{
	class A
	{
		public A(string text)
		{
			Console.WriteLine(text);
		}
	}

	class B
	{
		static A a1 = new A("a1");
		A a2 = new A("a2");

		/// <summary>
		/// 静态构造函数
		/// </summary>
		static B()
		{
			a1 = new A("a3");
		}

		public B()
		{
			a2 = new A("a4");
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			B b = new B();
		}
	}
}
