using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodingInterviewsCSharp
{
	/// <summary>
	/// 可行的解法：加同步锁前后两次判断实例是否已存在
	/// </summary>
	public sealed class Singleton3
	{
		private Singleton3()
		{
		}

		private static object syncObj = new object();

		private static Singleton3 instance = null;
		public static Singleton3 Instance
		{
			get
			{
				if(instance == null)
				{
					lock(syncObj)
					{
						if (instance == null)
							instance = new Singleton3();
					}
				}
				return instance;
			}
		}
	}
}
