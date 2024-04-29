#ifndef UI_CORE_GLOBALMANAGER_H_
#define UI_CORE_GLOBALMANAGER_H_

#pragma once

#include "duilib/Core/WindowBuilder.h"
#include "duilib/Core/ColorManager.h"
#include "duilib/Core/FontManager.h"
#include "duilib/Core/ImageManager.h"
#include "duilib/Core/IconManager.h"
#include "duilib/Core/ZipManager.h"
#include "duilib/Core/LangManager.h"
#include "duilib/Core/DpiManager.h"
#include "duilib/Core/TimerManager.h"

#include <string>
#include <vector>
#include <map>

namespace ui 
{
	class IRenderFactory;
;
/**
* ȫ�����Թ�������
* ���ڹ���һЩȫ�����ԵĹ����࣬����ȫ����ʽ��global.xml�����������õ�
*/
class UILIB_API GlobalManager
{
private:
	GlobalManager();
	~GlobalManager();
	GlobalManager(const GlobalManager&) = delete;
	GlobalManager& operator = (const GlobalManager&) = delete;

public:
	/** ��ȡ��������
	*/
	static GlobalManager& Instance();

public:
	/** ��ʼ��ȫ�����ú���
	 * @param[in] strResourcePath ��Դ·��λ��
	 * @param[in] callback �����Զ���ؼ�ʱ��ȫ�ֻص�����
	 * @param[in] bAdaptDpi �Ƿ����� DPI ����
	 * @param[in] theme ����Ŀ¼����Ĭ��Ϊ themes\\default
	 * @param[in] language ʹ�����ԣ�Ĭ��Ϊ lang\\zh_CN
	 */
	void Startup(const std::wstring& strResourcePath, const CreateControlCallback& callback, bool bAdaptDpi, const std::wstring& theme = L"themes\\default", const std::wstring& language = L"lang\\zh_CN");

	/** �ͷ�ȫ����Դ
	 */
	void Shutdown();

public:
	/** ����Ƥ����Դ����Ŀ¼
	 */
	void SetResourcePath(const std::wstring& strPath);

	/** ��ȡ��ǰ��Դ����Ŀ¼
	 */
	const std::wstring& GetResourcePath();

	/** ���õ�ǰ�����ļ�·��
	*/
	void SetLanguagePath(const std::wstring& strPath);

	/** ��ȡ��ǰ�����ļ�·��
	*/
	const std::wstring& GetLanguagePath();

	/** ������Դ���ط�ʽ�����ض�Ӧ����Դ·��
	 * @param[in] path Ҫ��ȡ����Դ·��
	 * @param [in] windowResPath ���ڶ�Ӧ����Դ���Ŀ¼�����磺"basic\"
	 * @param [in] resPath ��Դ�ļ�·�������磺"../public/button/btn_wnd_gray_min_hovered.png"
	 * @return ���õ���������Դ·�������磺
	          ��1�������ʹ��ZIPѹ���������أ�"resources\themes\default\public\button\btn_wnd_gray_min_hovered.png"
			  ��2�����δʹ��ZIPѹ���������أ�"D:\<��������Ŀ¼>\resources\themes\default\public\button\btn_wnd_gray_min_hovered.png"
	 */
	std::wstring GetResFullPath(const std::wstring& windowResPath, const std::wstring& resPath);

	/** ���¼���Ƥ����Դ
	 * @param[in] resourcePath ��Դ·��
	 */
	void ReloadSkin(const std::wstring& resourcePath);

	/** ���¼���������Դ
	 * @param[in] languagePath ������Դ·��
	 */
	void ReloadLanguage(const std::wstring& languagePath, bool invalidateAll = false);

	/** ���һ�����ڽӿڣ���Ҫ���ڻ������л�����֮����ػ桢��Դͬ���Ȳ�����
	*/
	void AddWindow(Window* pWindow);

	/** �Ƴ�һ������
	*/
	void RemoveWindow(Window* pWindow);

	/** ��ȡ���ƽӿ������
	 */
	IRenderFactory* GetRenderFactory();

	/** ���һ��ȫ�� Class ����
	 * @param[in] strClassName ȫ�� Class ����
	 * @param[in] strControlAttrList �����б���Ҫ�� XML ת��
	 */
	void AddClass(const std::wstring& strClassName, const std::wstring& strControlAttrList);

	/** ��ȡһ��ȫ�� class ���Ե�ֵ
	 * @param[in] strClassName ȫ�� class ����
	 * @return �����ַ�����ʽ�� class ����ֵ
	 */
	std::wstring GetClassAttributes(const std::wstring& strClassName);

	/** ��ȫ��������ɾ������ class ����
	 * @return ���ػ����������
	 */
	void RemoveAllClasss();

public:
	/** ��ȡ��ɫ������
	*/
	ColorManager& Color();

	/** ��ȡ���������
	*/
	FontManager& Font();

	/** ��ȡͼƬ������
	*/
	ImageManager& Image();

#ifdef UILIB_IMPL_WINSDK
	/** ��ȡICON��Դ������
	*/
	IconManager& Icon();

	/** RichEdit������DLL, ���ز����ؾ��
	*/
	HMODULE GetRichEditModule();

#endif

	/** ��ȡZip������
	*/
	ZipManager& Zip();

	/** ��ȡDPI������
	*/
	DpiManager& Dpi();

	/** ��ȡ��ʱ��������
	*/
	TimerManager& Timer();

	/** ������֧�ֹ�����
	*/
	LangManager& Lang();

public:
	/** ���� XML ����һ�� Box
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 * @return ָ������ģ��Ķ���ָ��
	 */
	Box* CreateBox(const std::wstring& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/** ���� XML �ڻ����в���ָ�� Box�����û���򴴽�
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 * @return ָ������ģ��Ķ���ָ��
	 */
	Box* CreateBoxWithCache(const std::wstring& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/** ʹ�� XML ���ָ�� Box
	 * @param[in] pUserDefinedBox Ҫ���� box ָ��
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 */
	void FillBox(Box* pUserDefinedBox, const std::wstring& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/** ʹ�ù������Ļ������ָ�� Box�����û�������¹���
	 * @param[in] pUserDefinedBox Ҫ���� box ָ��
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 */
	void FillBoxWithCache(Box* pUserDefinedBox, const std::wstring& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/** �Զ���ؼ��������ȫ�ֻص�����
	 * @param[in] strControlName �Զ���ؼ�����
	 * @return ����һ���Զ���ؼ��Ķ���ָ��
	 */
	Control* CreateControl(const std::wstring& strControlName);

	/** ����ú���������UI�߳��е��õģ����ж��Ա���
	*/
	void AssertUIThread();

private:
	/**
	 * @brief ����ȫ����Դ
	 * @return ��
	 */
	void LoadGlobalResource();

	/** �ӻ�����ɾ������ͼƬ
	 */
	void RemoveAllImages();

private:

	/** ��Ⱦ�������ӿ�
	*/
	std::unique_ptr<IRenderFactory> m_renderFactory;

	/** ȫ�ֵ���Դ·����������ʱ���޸��������
	*/
	std::wstring m_resourcePath; 

	/** ȫ�������ļ�·��
	*/
	std::wstring m_languagePath; 
	
	/** ���ڹ�������ӿڣ�KEY��XML�ļ�·����VALUE�Ǵ��ڹ�������ӿڣ��Ѿ��������XML���ɱ����ظ�������
	*/
	std::map<std::wstring, std::unique_ptr<WindowBuilder>> m_builderMap;

	/** �ؼ����������������û��Զ���ؼ��Ĵ���
	*/
	CreateControlCallback m_pfnCreateControlCallback;

	/** ÿ��Class������(KEY)�������б�(VALUE)������global.xml�ж����Class��
	*/
	std::map<std::wstring, std::wstring> m_globalClass;

	/** ���߳�ID
	*/
	uint32_t m_dwUiThreadId;

	/** ���еĴ����б�
	*/
	std::vector<Window*> m_windowList;

	/** ��ɫ������
	*/
	ColorManager m_colorManager;

	/** ���������
	*/
	FontManager m_fontManager;

	/** ͼƬ������
	*/
	ImageManager m_imageManager;

	/** ZIPѹ����������
	*/
	ZipManager m_zipManager;

	/** DPI������
	*/
	DpiManager m_dpiManager;

	/** ��ʱ��������
	*/
	TimerManager m_timerManager;

	/** �����Թ�����
	*/
	LangManager m_langManager;

#ifdef UILIB_IMPL_WINSDK
	/** ICON��Դ������
	*/
	IconManager m_iconManager;

	/** RichEdit������DLL, ���ز����ؾ��
	*/
	HMODULE m_hRichEditModule;
#endif
};

} // namespace ui

#endif // UI_CORE_GLOBALMANAGER_H_
