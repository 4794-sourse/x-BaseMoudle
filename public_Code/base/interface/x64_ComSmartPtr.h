#pragma once

//Interface为接口类型，IID_Interface为接口的IID
template<typename Interface, const IID& IID_Interface>
class smart_object {
public:
	typedef Interface _Interface;

	inline const static IID& GetInterfaceIID() {
		return IID_Interface;
	}
};

template<typename smart_object>
class smart_ptr {
public:
	typedef typename smart_object::_Interface Interface;
	typedef smart_object ThisIIID;

	smart_ptr() : m_interface(NULL) {

	}

	~smart_ptr() 
	{
		Release();
	}

	void AddRef() {

		if (m_interface) {
			m_interface->addref();
		}
	}

	void Release() {
		if (m_interface) {
			m_interface->release();
		}
	}

	void Attach(Interface* pInterface) throw()
	{
		Release();
		m_interface = pInterface;
	}

	Interface* operator->() const {
		
		if (m_interface == nullptr) {
			x64_ASSERT(m_interface != nullptr);
		}
		return m_interface;
	}

	Interface* Detach()
	{
		Interface* const old = m_interface;
		m_interface = nullptr;
		return old;
	}

	explicit smart_ptr(smart_ptr* p)
		: m_interface(nullptr)
	{
		if (p == nullptr) {
			x64_ASSERT(false);
		}
		else {
			m_interface = p->m_interface;
			AddRef();
		}
	}

	Interface** operator&() throw()
	{
		Release();
		m_interface = nullptr;
		return &m_interface;
	}

	//对象的唯一来源
	smart_ptr& operator=(Interface* pInterface)
	{
		if (m_interface != pInterface) {
			Interface* pOldInterface = m_interface;

			m_interface = pInterface;
			AddRef();

			if (pOldInterface != nullptr) {
				pOldInterface->release();
			}
		}
		return *this;
	}

	//对外的查询接口
	template<typename _InterfaceType> long QueryInterface(const IID& iid, _InterfaceType*& p)
	{
		if (m_interface != nullptr) {
			return m_interface->query_interface(iid, reinterpret_cast<void**>(&p));
		}
		return -1;
	}

	static const IID& _getIID() {
		ThisIIID::GetInterfaceIID();
	}
private:
	Interface* m_interface;
};

#define X64_SMART_PTR(Interface, ptr) \
	typedef smart_ptr<smart_object<Interface, IID_ ## Interface>> ptr;