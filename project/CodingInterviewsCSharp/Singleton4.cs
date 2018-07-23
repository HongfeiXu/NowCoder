using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingInterviewsCSharp
{
	/// <summary>
	/// 强烈推荐的解法一：利用静态构造函数
	/// </summary>
	public sealed class Singleton4
	{
		private Singleton4()
		{
		}

		// 在初始化静态变量 instance 的时候创建一个实例
		// 实例 instance 不是在第一次调用属性 Singleton4.Instance 的时候被创建，
		// 而是在第一次用到 Singleton4 的时候被创建，可能会降低内存的使用效率
		private static Singleton4 instance = new Singleton4();	
		public static Singleton4 Instance
		{
			get
			{
				return instance;
			}
		}
	}
}
