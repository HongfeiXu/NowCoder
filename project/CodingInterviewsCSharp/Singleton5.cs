using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingInterviewsCSharp
{
	/// <summary>
	/// 强烈推荐的解法二：实现按需创建实例
	/// </summary>
	public sealed class Singleton5
	{
		private Singleton5()
		{
		}

		public static Singleton5 Instance
		{
			get
			{
				return Nested.instance;
			}
		}

		private class Nested
		{
			static Nested()
			{
			}
			// 当第一次用到 Nested 类型的时候，调用静态构造函数创建 Singleton5 的实例 instacne
			// 因为只在属性 Singleton5.Instance 中用到，所以做到了按需创建
			internal static readonly Singleton5 instance = new Singleton5();
		}

	}
}
