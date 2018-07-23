using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingInterviewsCSharp
{
	/// <summary>
	/// 不好的解法一：只适用于单线程环境
	/// </summary>
	public sealed class Singleton1
	{
		private Singleton1()
		{
		}

		private static Singleton1 instance = null;
		public static Singleton1 Instance
		{
			get
			{
				if (instance == null)
					instance = new Singleton1();
				return instance;
			}
		}
	}
}
