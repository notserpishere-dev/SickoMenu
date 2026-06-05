#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

TaskCompletedEvent::TaskCompletedEvent(const EVENT_PLAYER& source, const std::optional<TaskTypes__Enum>& taskType, const Vector2& position, const std::optional<SystemTypes__Enum>& startAt, const std::optional<SystemTypes__Enum>& targetSystem) : EventInterface(source, EVENT_TYPES::EVENT_TASK) {
	this->taskType = taskType;
	this->position = position;
	this->systemType = GetSystemTypes(position);
	this->startAt = startAt;
	this->targetSystem = targetSystem;
}

std::string TaskCompletedEvent::GetDetailedName() {
	// systemType is where the task was completed; used as the room for the generic case and as a
	// fallback target for Divert Power.
	return FormatTaskName(taskType, startAt, targetSystem, systemType);
}

void TaskCompletedEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("(%s)", GetColorName(source.colorId).c_str());
	ImGui::SameLine();
	ImGui::Text("> %s", GetDetailedName().c_str());
	ImGui::SameLine();
	ImGui::Text("[%s ago]", std::format("{:%OM:%OS}", (std::chrono::system_clock::now() - this->timestamp)).c_str());
}

void TaskCompletedEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "TASK");
	ImGui::SameLine();
	ImGui::Text("]");
}
