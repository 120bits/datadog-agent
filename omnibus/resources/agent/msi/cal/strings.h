#pragma once
extern std::wstring secretUserUsername;
extern std::wstring secretUserDescription;
extern std::wstring datadog_path;
extern std::wstring datadog_key_root;
extern std::wstring datadog_key_secret_key;
extern std::wstring datadog_key_secrets;
extern std::wstring datadog_acl_key_secrets;
extern std::wstring datadog_acl_key_datadog;
extern std::wstring installStepsKey;
extern std::wstring datadog_service_name;

extern std::wstring ddAgentUserName;
extern std::wstring ddAgentUserPasswordProperty;
extern std::wstring ddAgentUserDescription;

extern std::wstring traceService;
extern std::wstring processService;
extern std::wstring agentService;

extern std::wstring propertyDDUserCreated;
extern std::wstring propertySecretUserCreated;
extern std::wstring propertySecretPasswordWritten;
extern std::wstring propertyRollbackState;

extern std::wstring programdataroot;
extern std::wstring logfilename;
extern std::wstring authtokenfilename;
extern std::wstring datadogyamlfile;
extern std::wstring confddir;
extern std::wstring logdir;

// installation steps
extern std::wstring strDdUserCreated;
extern std::wstring strDdUserPasswordChanged;
extern std::wstring strFilePermissionsChanged;
extern std::wstring strAddDdUserToPerfmon;
extern std::wstring strAddDdSecretUser;
extern std::wstring strChangedRegistryPermissions;


void toMbcs(std::string& target, LPCWSTR src);

#define MAX_CUSTOM_PROPERTY_SIZE        128