using System;
namespace Singularity;

static class Singularity
{
	const String DllName = "Singularity.dll";

	public delegate void GenericDelegate();
	public delegate void DoubleDelegate(double v);
	public delegate void MessageDelegate(String message);

	public enum GraphicsBackend
	{
		D3D11,
	}

	[CRepr,Ordered]
	public struct AppConfig
	{
		public String title;
		public int Width;
		public int Height;
		public GraphicsBackend graphicsBackend;
		public GenericDelegate OnCreate;
		public GenericDelegate OnExit;
		public DoubleDelegate OnUpdate;
		public DoubleDelegate OnRender;
	}
	[CRepr,Ordered]
	public struct Time
	{
		public float deltaTime;
		public float runtime;
	}

	[Import(DllName)]
	public extern static void Start(AppConfig* config,MessageDelegate errorCallback);
	[Import(DllName)]
	public extern static Time GetTimeData();

	[Import(DllName)]
	public extern static uint64 CreateContainer(void* data,int numberOfelements);
	[Import(DllName)]
	private static extern void GetContainerData(uint64 id, out void* data,out int numberOfElements);
	[Import(DllName)]
	public extern static void UpdateContainer(uint64 id,void* newData,int newNumberOfElements);
	[Import(DllName)]
	public extern static void DeleteContainer(out uint64 id);
	[Import(DllName)]
	public extern static void ClearContainer(uint64 id);

	public static void GetContainerData<T>(uint64 id,out T[] c)
	{
		c = default;
		if(id == 0) return;

		void* data;
		int size;
		GetContainerData(id,out data,out size);

		if(data == null || size == -1) return;

		var tp = (T*)data;
		c = new T[size];
		for(var i < size)
		{
			c[i] = *(tp + i);
		}
	}
}