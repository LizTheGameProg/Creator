namespace GAME_ENGINE
{
	template <class T>
	bool Handler<T>::Initialize()
	{
		isInitialized = OnInitialize();
		return isInitialized;
	}

	template <class T>
	void Handler<T>::DeInitialize()
	{
		OnDeInitialize();
	}

	template <class T>
	T const & Handler<T>::Get()
	{
		return Access();
	}

	template <class T>
	T & Handler<T>::Access()
	{
		return *instance;
	}
}