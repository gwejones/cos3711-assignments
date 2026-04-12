#pragma once

/**
 * Central XML schema for serializing and deserializing StudentList.
 */
struct StudentListXmlSchema
{
    static constexpr const char *kFileName = "student_list.xml";
    static constexpr const char *kRootElement = "StudentList";
    static constexpr const char *kStudentElement = "student";
    static constexpr const char *kNumberElement = "number";
    static constexpr const char *kModulesElement = "modules";
    static constexpr const char *kModuleElement = "module";
    static constexpr const char *kCodeElement = "code";
    static constexpr const char *kMarkElement = "mark";
};
