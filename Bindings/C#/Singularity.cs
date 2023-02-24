using System.Runtime.InteropServices;

namespace Singularity
{
    public static class Singularity
    {
        private const string DllName = "Singularity.dll";
        
        public delegate void GenericDelegate();
        public delegate void DoubleDelegate(double v);
        public delegate void MessageDelegate(string message);
        
        public enum GraphicsBackend
        {
            D3D11,
        }

        [StructLayout(LayoutKind.Sequential,CharSet = CharSet.Unicode)]
        public struct AppConfig
        {
            public string Title;
            public int Width;
            public int Height;
            public GraphicsBackend GraphicsBackend;
            public GenericDelegate OnCreate;
            public GenericDelegate OnExit;
            public DoubleDelegate OnUpdate;
            public DoubleDelegate OnRender;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Time
        {
            public double deltaTime;
            public float runtime;
        }

        [DllImport(DllName)]
        public static extern void Start(AppConfig config,MessageDelegate errorCallback);
        [DllImport(DllName)]
        public static extern Time GetTimeData();

        [DllImport(DllName)]
        public static extern unsafe ulong CreateContainer(void* data, int numberOfElements);
        [DllImport(DllName)]
        private static extern unsafe void GetContainerData(ulong id, out void* data,out int numberOfElements);
        [DllImport(DllName)]
        public static extern unsafe void UpdateContainer(ulong id, void* newData,int newNumberOfElements);
        [DllImport(DllName)]
        public static extern void DeleteContainer(out ulong id);
        [DllImport(DllName)]
        public static extern void ClearContainer(ulong id);

        public static unsafe T[] GetContainerData<T>(ulong id)
        {
            if(id == 0) return default;

            GetContainerData(id, out var data, out var size);
            if(data == null) return default;
            
            var tp = (T*)data;
            var a = new T[size];
            for(var i = 0; i < size; i++)
            {
                a[i] = *(tp + i);
            }
            return a;
        }

    }
}