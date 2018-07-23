using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingInterviewsCSharp
{
	/// <summary>
	/// 不好的解法二：虽然在多线程环境中能工作，但效率不高
	/// </summary>
	public sealed class Singleton2
	{
		private Singleton2()
		{
		}

		private static readonly object syncObj = new object();

		private static Singleton2 instance = null;
		public static Singleton2 Instance
		{
			get
			{
				lock(syncObj)
				{
					if(instance == null)
					{
						instance = new Singleton2();
					}
				}
				return instance;
			}
		}
	}
}
