#include "widget.h"


namespace Editor {

	void initEditor();
	void showEditor_Hierarchy();
	void showEditor_WorldEditor();
	void showEditor_AssetTracker();
	void showEditor_Property();

	void terminateEditor();

}

// v3.0 Hierarchy
/*
void __editorHierarchyOwn_initSelectedEntityVariable(EntityObjectGUI* entityObjectGUI)
{
	_selectedEntityObjectGUI = entityObjectGUI;

	_selectedEntityName = std::vector<char>(_selectedEntityObjectGUI->_entity->name.begin(), _selectedEntityObjectGUI->_entity->name.end());
	_selectedEntityName.resize(128);

	_selectedTranslation = _selectedEntityObjectGUI->_entity->transform->getPosition();
	_selectedRotation = _selectedEntityObjectGUI->_entity->transform->getRotation();
	_selectedDimension = _selectedEntityObjectGUI->_entity->transform->getDimension();

	_selectedGeometryType = _selectedEntityObjectGUI->_geometry;

	for (int i = 0; i < (int)ResourcesTextureIndex::__Index_Size; i++)
	{
		if (_selectedEntityObjectGUI->_texture->getTextureID() == resourcesTexture[i]->getTextureID())
		{
			_selectedTextureIndex = i;
		}
	}

}

void __editorHierarchyOwn_addEntityObject(EntityObjectGUI* entityObjectGUIData)
{
	_entityObjectGUI_List.push_back(entityObjectGUIData);

	++_differentEntityNameIndex;
}

void __editorHierarchyOwn_addNewEntityObject()
{
	EntityObjectGUI* newEntityObjectGUI = new EntityObjectGUI;

	newEntityObjectGUI->_inheritOrderIndex.clear();
	newEntityObjectGUI->_parent = nullptr;
	newEntityObjectGUI->_child.clear();

	newEntityObjectGUI->_entity = new Entity();
	newEntityObjectGUI->_entity->id = _differentEntityNameIndex;
	newEntityObjectGUI->_entity->name = "New entity " + std::to_string(_differentEntityNameIndex);
	newEntityObjectGUI->_entity->parent = nullptr;
	newEntityObjectGUI->_entity->child.clear();
	newEntityObjectGUI->_entity->transform->transformLocal(_camera->transform->getPosition(), glm::vec3(0.0f), glm::vec3(1.0f));
	newEntityObjectGUI->_entity->group = 0;

	newEntityObjectGUI->_geometry = Mesh::DefaultGeometry::SQUARE;
	newEntityObjectGUI->_mesh = new Mesh(newEntityObjectGUI->_geometry);
	newEntityObjectGUI->_texture = resourcesTexture[(int)ResourcesTextureIndex::Glass];

	newEntityObjectGUI->visibility = true;


	_entityObjectGUI_List.push_back(newEntityObjectGUI);

	__editorHierarchyOwn_initSelectedEntityVariable(newEntityObjectGUI);

	++_differentEntityNameIndex;

}

DoubleLinkList<EntityObjectGUI*>::iterator __editorHierarchyOwn_deleteEntityObject(EntityObjectGUI* entityObjectGUIData, int index)
{
	DoubleLinkList<EntityObjectGUI*>::iterator nextIter = entityObjectGUIData->_child.begin();

	if (entityObjectGUIData->_parent == nullptr)
	{
		nextIter = _entityObjectGUI_List.erase(index);
	}
	else
	{
		for (auto iter = entityObjectGUIData->_parent->_entity->child.begin(); iter != entityObjectGUIData->_parent->_entity->child.end(); iter++)
		{
			if (*iter == entityObjectGUIData->_entity)
			{
				iter = entityObjectGUIData->_parent->_entity->child.erase(iter);
				break;
			}
		}
		nextIter = entityObjectGUIData->_parent->_child.erase(index);

		entityObjectGUIData->_entity->parent = nullptr;
		entityObjectGUIData->_parent = nullptr;
	}

	int i = 0;
	for (DoubleLinkList<EntityObjectGUI*>::iterator iter = entityObjectGUIData->_child.begin(); iter != entityObjectGUIData->_child.end(); iter++)
	{
		// alway pass 0 be index is because it will alway delete the first node, and then the second node will become first node
		// but make sure it won't happen any error, so we use i for more safety
		DoubleLinkList<EntityObjectGUI*>::iterator newIter = __editorHierarchyOwn_deleteEntityObject(*iter, i);
		if (*iter == *newIter)
		{
			iter++;
			i++;
		}
		else
		{
			iter = newIter;
		}
	}

	return nextIter;
}

void __editorHierarchyOwn_setEntityParentObject(EntityObjectGUI* newParent, EntityObjectGUI* child, int& childIndexInOldParent)
{
	if (child->_parent == newParent) return;

	if (child->_parent == nullptr)
	{
		_entityObjectGUI_List.erase(childIndexInOldParent);
	}
	else
	{
		EntityObjectGUI* oldParent = child->_parent;

		// erase EntityObjectGUI from child of old parant EntityObjectGUI
		oldParent->_child.erase(childIndexInOldParent);

		// erase real Entity from the child of old parant Entity
		for (auto iter = oldParent->_entity->child.begin(); iter != oldParent->_entity->child.end(); iter++)
		{
			const Entity* temp = *iter;
			if (temp == child->_entity)
			{
				iter = oldParent->_entity->child.erase(iter);
				break;
			}
		}
	}

	// push newChild to parent
	if (newParent != nullptr)
	{
		newParent->_child.push_back(child);
		newParent->_entity->child.push_back(child->_entity);

		child->_parent = newParent;
		child->_entity->parent = newParent->_entity;
	}
	else
	{
		_entityObjectGUI_List.push_back(child);

		child->_parent = nullptr;
		child->_entity->parent = nullptr;
	}

}

bool __editorHierarchyOwn_InheritDragDropAction(EntityObjectGUI* entityObjectGUI, int& index)
{
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_index = *(const int*)payload->Data;

			__editorHierarchyOwn_setEntityParentObject(entityObjectGUI, _draggingEntityObjectGUI, payload_index);

			_draggingEntityObjectGUI = nullptr;

		}
		ImGui::EndDragDropTarget();
	}
	return false;

}

void __editorHierarchyOwn_DragDropAction(EntityObjectGUI* entityObjectGUI, int& index)
{
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
	{
		// Set payload to carry the index of our item (could be anything)
		ImGui::SetDragDropPayload("ENTITY_CELL", &index, sizeof(int));

		_isDragging = true;
		_draggingEntityObjectGUI = entityObjectGUI;

		// Display preview (could be anything, e.g. when dragging an image we could decide to display
		// the filename and a small preview of the image, etc.)
		ImGui::Text("Move %s", entityObjectGUI->_entity->name.c_str());
		ImGui::EndDragDropSource();

	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_draggingIndex = *(const int*)payload->Data;

			// when dragging node and target node are same parent
			if (_draggingEntityObjectGUI->_parent == entityObjectGUI->_parent)
			{
				// if they parent are nullptr meaning that it is a start node and in the _entityObjectGUI_List, so do change the order of them in _entityObjectGUI_List
				if (_draggingEntityObjectGUI->_parent == nullptr)
				{
					// if the target node is above of the dragging node, then move the draging node order above the target node
					if ((index - payload_draggingIndex) > 0)
						_entityObjectGUI_List.moveNode(payload_draggingIndex, index, false);
					// otherwise the target node is below of the dragging node, then move the draging node order below the target node
					else
						_entityObjectGUI_List.moveNode(payload_draggingIndex, index, true);
				}
				// otherwise they dragging node and target node both are the child node of the same parent, so just do change the order of them
				else {
					if ((index - payload_draggingIndex) > 0)
						entityObjectGUI->_parent->_child.moveNode(payload_draggingIndex, index, false);
					else
						entityObjectGUI->_parent->_child.moveNode(payload_draggingIndex, index, true);
				}
			}
			// when dragging node and target node are having different parent
			else if (_draggingEntityObjectGUI->_parent != entityObjectGUI->_parent)
			{
				EntityObjectGUI* targetParent = entityObjectGUI->_parent;

				// change the parent of dragging node to same with target node
				__editorHierarchyOwn_setEntityParentObject(targetParent, _draggingEntityObjectGUI, payload_draggingIndex);

				// if target parent are null meaning that it is a start node and in the _entityObjectGUI_List, and always change the order of dragging node to above the target node
				if (targetParent == nullptr)
					_entityObjectGUI_List.moveNode(_entityObjectGUI_List.size() - 1, index);
				// otherwise just do change the order of them in the parent's child list
				else
					targetParent->_child.moveNode(targetParent->_child.size() - 1, index);

			}

			_draggingEntityObjectGUI = nullptr;

		}
		ImGui::EndDragDropTarget();
	}


}

void __editorHierarchyOwn_defineWithChildSelectedState(EntityObjectGUI* entityObjectGUI, int& index)
{
	ImGui::PushID(index);
	bool isOpen = ImGui::TreeNodeEx(entityObjectGUI->_entity->name.c_str(), (_selectedEntityObjectGUI == entityObjectGUI) ? (_entityHaveChild_Flags | ImGuiTreeNodeFlags_Selected) : _entityHaveChild_Flags);
	ImGui::PopID();

	if (ImGui::IsItemClicked())
	{
		__editorHierarchyOwn_initSelectedEntityVariable(entityObjectGUI);
	}

	__editorHierarchyOwn_DragDropAction(entityObjectGUI, index);

	if (isOpen)
	{
		int i = 0;
		for (DoubleLinkList<EntityObjectGUI*>::iterator iter = entityObjectGUI->_child.begin(); iter != entityObjectGUI->_child.end();)
		{
			DoubleLinkList<EntityObjectGUI*>::iterator newIter = __editorHierarchyOwn_showEntityToList(*iter, i);
			if (*iter == *newIter)
			{
				iter++;
				i++;
			}
			else
			{
				iter = newIter;
			}
		}
		ImGui::TreePop();
	}

}

void __editorHierarchyOwn_defineWithoutChildSelectedState(EntityObjectGUI* entityObjectGUI, int& index)
{
	ImGui::PushID(index);
	bool isOpen = ImGui::TreeNodeEx(entityObjectGUI->_entity->name.c_str(), (_selectedEntityObjectGUI == entityObjectGUI) ? (_entityNullChild_Flags | ImGuiTreeNodeFlags_Selected) : _entityNullChild_Flags);
	ImGui::PopID();

	if (ImGui::IsItemClicked())
	{
		__editorHierarchyOwn_initSelectedEntityVariable(entityObjectGUI);
	}

	__editorHierarchyOwn_DragDropAction(entityObjectGUI, index);

	if (isOpen)
	{
		// pressed action here
	}

}

bool __editorHierarchyOwn_isOneOfChild(EntityObjectGUI* objectEntityObjectGUI, EntityObjectGUI* targetEntityObjectGUI)
{
	if (objectEntityObjectGUI == nullptr) return false;

	for (auto iter = objectEntityObjectGUI->_child.begin(); iter != objectEntityObjectGUI->_child.end(); iter++)
	{
		if (*iter == targetEntityObjectGUI)
		{
			return true;
		}
		if (__editorHierarchyOwn_isOneOfChild(*iter, targetEntityObjectGUI))
		{
			return true;
		}
	}

	return false;
}

DoubleLinkList<EntityObjectGUI*>::iterator __editorHierarchyOwn_showEntityToList(DoubleLinkList<EntityObjectGUI*>::iterator entityObjectGUI_iter, int& index)
{
	if (ImGui::IsKeyDown(GLFW_KEY_DELETE) && (_draggingEntityObjectGUI == *entityObjectGUI_iter))
	{
		return __editorHierarchyOwn_deleteEntityObject(*entityObjectGUI_iter, index);
	}

	ImGui::Separator();

	ImGui::PushID((*entityObjectGUI_iter)->_entity->name.c_str() + index);
	ImGui::Checkbox("", &(*entityObjectGUI_iter)->visibility);
	ImGui::PopID();
	ImGui::SameLine(); ImGui::Spacing(); ImGui::SameLine();

	if (_isDragging && ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Left))
	{
		_isDragging = false;
	}

	if (ImGui::IsMouseDragging(ImGuiMouseButton_::ImGuiMouseButton_Left) && _isDragging && (_draggingEntityObjectGUI != *entityObjectGUI_iter))
	{

		if (!__editorHierarchyOwn_isOneOfChild(_draggingEntityObjectGUI, *entityObjectGUI_iter))
		{
			ImGui::Selectable("P >", false, ImGuiSelectableFlags_::ImGuiSelectableFlags_None, ImVec2(18.0f, 0.0f));
			__editorHierarchyOwn_InheritDragDropAction(*entityObjectGUI_iter, index);
			ImGui::SameLine();
		}
		else
		{
			ImGui::Selectable("", false, ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled, ImVec2(18.0f, 0.0f));
			//__editorHierarchyOwn_InheritDragDropAction(entityObjectGUI, index, inheritCount);
			ImGui::SameLine();
		}

	}
	else
	{
		ImGui::Selectable("", false, ImGuiSelectableFlags_::ImGuiSelectableFlags_Disabled, ImVec2(18.0f, 0.0f));
		if (_draggingEntityObjectGUI != *entityObjectGUI_iter)
		{
			__editorHierarchyOwn_InheritDragDropAction(*entityObjectGUI_iter, index);
		}
		ImGui::SameLine();
	}

	if ((*entityObjectGUI_iter)->_child.size() != 0)
	{
		__editorHierarchyOwn_defineWithChildSelectedState(*entityObjectGUI_iter, index);
	}
	else
	{
		__editorHierarchyOwn_defineWithoutChildSelectedState(*entityObjectGUI_iter, index);
	}

	//ImGui::Text("%s", ImGui::IsItemClicked() ? "true" : "false"); ImGui::SameLine();

	return entityObjectGUI_iter;

}

DoubleLinkList<EntityObjectGUI*>::iterator __editorHierarchyOwn_filterEntityName(DoubleLinkList<EntityObjectGUI*>::iterator entityObjectGUI_iter, int& index)
{
	if (_filter.PassFilter((*entityObjectGUI_iter)->_entity->name.c_str()))
	{
		return __editorHierarchyOwn_showEntityToList(entityObjectGUI_iter, index);

	}

}

void showEditor_Hierarchy()
{
	if (ImGui::Begin("Hierarchy"))
	{
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.7f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.9f, 0.8f, 0.8f));
		if (ImGui::Button("+ Add New "))
		{
			__editorHierarchyOwn_addNewEntityObject();
		}
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		_filter.Draw();

		ImGui::Separator();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar;// | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("Entity", ImVec2(-FLT_MIN, -FLT_MIN), true, window_flags);
		{

			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Entities Hierarchy");
				ImGui::EndMenuBar();
			}
			int index = 0;
			for (DoubleLinkList<EntityObjectGUI*>::iterator iter = _entityObjectGUI_List.begin(); iter != _entityObjectGUI_List.end(); )
			{
				DoubleLinkList<EntityObjectGUI*>::iterator newIter = __editorHierarchyOwn_filterEntityName(iter, index);

				if (*iter == *newIter)
				{
					iter++;
					index++;
				}
				else
				{
					iter = newIter;
				}

			}

		}
		ImGui::EndChild();
		ImGui::PopStyleVar();

	}
	ImGui::End();


}
*/


// v1.0 Hierarchy
/*
class Hierarchy : public Widget {

public:

	DoubleLinkList<EntityObjectGUI*> entityObjectGUI;

	ImGuiTreeNodeFlags main_flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_SpanAvailWidth;
	ImGuiTreeNodeFlags node_flags;

private:

	void showEntityToList(EntityObjectGUI* parentEntity, int index)
	{
		//ImGui::PushID(index);

		ImGui::Separator();

		ImGui::Checkbox("", &parentEntity->visibility);
		ImGui::SameLine(); ImGui::Spacing();
		ImGui::SameLine();
		if (parentEntity->_entity.child.size() != 0)
		{
			node_flags = main_flags;
			if (selectedEntityObjectGUI == parentEntity)
				node_flags |= ImGuiTreeNodeFlags_Selected;

			if (ImGui::TreeNodeEx(parentEntity->_entity.name.c_str(), node_flags))
				//if (ImGui::TreeNode(currentEntityName.c_str()))
			{
				for (size_t i = 0; i < parentEntity->_entity.child.size(); i++)
				{
					//showEntityToList(parentEntity->_entity.child.findData(i), i);
				}
				ImGui::TreePop();
			}
		}
		else
		{
			node_flags = main_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			if (selectedEntityObjectGUI == parentEntity)
				node_flags |= ImGuiTreeNodeFlags_Selected;

			if (ImGui::TreeNodeEx(parentEntity->_entity.name.c_str(), node_flags))
				//if (ImGui::TreeNode(currentEntityName.c_str()))
			{
			}
		}

		if (ImGui::IsItemClicked())
			selectedEntityObjectGUI = parentEntity;

		
		//if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		//{
		//	// Set payload to carry the index of our item (could be anything)
		//	ImGui::SetDragDropPayload("DND_DEMO_CELL 1", &index, sizeof(int));
		//
		//	// Display preview (could be anything, e.g. when dragging an image we could decide to display
		//	// the filename and a small preview of the image, etc.)
		//	ImGui::Text("Move %s", parentEntity->name.c_str());
		//	ImGui::EndDragDropSource();
		//}
		//
		//if (ImGui::BeginDragDropTarget())
		//{
		//	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL 1"))
		//	{
		//		IM_ASSERT(payload->DataSize == sizeof(int));
		//		int payload_n = *(const int*)payload->Data;
		//
		//		if ((index - payload_n) > 0)
		//			entity.moveNode(payload_n, index, false);
		//		else
		//			entity.moveNode(payload_n, index, true);
		//
		//	}
		//	ImGui::EndDragDropTarget();
		//}
		

		//ImGui::PopID();
	}

	// Inherited via Widget
	virtual void action() override
	{
		static int e = 0;
		ImGui::RadioButton("Move", &e, 0); ImGui::SameLine();
		ImGui::RadioButton("In To", &e, 1); ImGui::SameLine();
		ImGui::RadioButton("Out To", &e, 2);

		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.7f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.9f, 0.8f, 0.8f));
		if (ImGui::Button("+ Click "))
		{
			EntityObjectGUI* temp = new EntityObjectGUI;
			temp->_entity.name = "New entity";
			temp->visibility = true;
			temp->_mesh = new Mesh(Mesh::DefaultGeometry::SQUARE);
			temp->_texture = resourcesTexture[(int)ResourcesTextureIndex::None];
			temp->_entity.child.clear();
			temp->_entity.parent = nullptr;

			entityObjectGUI.push_back(temp);
		}
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		static ImGuiTextFilter filter;
		filter.Draw();

		ImGui::Separator();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar;// | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("Entity", ImVec2(-FLT_MIN, -FLT_MIN), true, window_flags);
		{

			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Entities Hierarchy");
				ImGui::EndMenuBar();
			}

			//ImGui::Columns(2);
			
			//for (auto iter = enity.begin(); iter != enity.end(); iter++)
			//{
			//	if (filter.PassFilter(iter->name.c_str()))
			//	{
			//		const std::string item = iter->name;
			//
			//		if (iter->child.size() == 0)
			//		{
			//			ImGui::Selectable(iter->name.c_str());
			//		}
			//		else
			//		{
			//			if (ImGui::TreeNode(iter->name.c_str()))
			//			{
			//				for (auto iterChild = iter->child.begin(); iterChild != iter->child.end(); iterChild++)
			//				{
			//					ImGui::Selectable(iter->name.c_str());
			//				}
			//				ImGui::TreePop();
			//			}
			//		}
			//
			//		if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
			//		{
			//			n_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
			//			if (n_next >= 0 && n_next < name.size())
			//			{
			//				enity[i].name = enity[n_next].name;
			//				enity[n_next].name = item;
			//				ImGui::ResetMouseDragDelta();
			//			}
			//		}
			//
			//	}
			//
			//}
			

			
			//for (int i = 0; i < name.size(); i++)
			//{
			//	if (filter.PassFilter(enitySlot[i].name.c_str()))
			//	{
			//		const std::string item = enitySlot[i].name;
			//
			//		//ImGui::Checkbox("", &enity[i].visibility);
			//		//ImGui::NextColumn();
			//		//char buf[32];
			//		//sprintf_s(buf, "%03d", i);
			//		//ImGui::Selectable(enitySlot[i].name.c_str());
			//		ImGui::Button(enitySlot[i].name.c_str(), ImVec2(-FLT_MIN, 0.0f));
			//		//ImGui::NextColumn();
			//
			//		if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
			//		{
			//			n_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
			//			if (n_next >= 0 && n_next < name.size())
			//			{
			//				enitySlot[i].name = enitySlot[n_next].name;
			//				enitySlot[n_next].name = item;
			//				ImGui::ResetMouseDragDelta();
			//			}
			//		}
			//	}
			//
			//}
			

			for (int i = 0; i < entityObjectGUI.size(); i++)
			{
				ImGui::PushID(i);

				EntityObjectGUI* tempNode = entityObjectGUI.findData(i);
				std::string currentEntityName = tempNode->_entity.name;

				if (filter.PassFilter(currentEntityName.c_str()))
				{
					ImGui::Separator();

					ImGui::Checkbox("", &tempNode->visibility);
					ImGui::SameLine(); ImGui::Spacing();
					ImGui::SameLine();
					if (tempNode->_entity.child.size() != 0)
					{
						node_flags = main_flags;
						if (selectedEntityObjectGUI == tempNode)
							node_flags |= ImGuiTreeNodeFlags_Selected;

						if (ImGui::TreeNodeEx(currentEntityName.c_str(), node_flags))
							//if (ImGui::TreeNode(currentEntityName.c_str()))
						{
							for (size_t i = 0; i < tempNode->_entity.child.size(); i++)
							{
								//showEntityToList(tempNode->_entity.child.findData(i), i);
							}
							ImGui::TreePop();
						}
					}
					else
					{
						node_flags = main_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
						if (selectedEntityObjectGUI == tempNode)
							node_flags |= ImGuiTreeNodeFlags_Selected;

						if (ImGui::TreeNodeEx(currentEntityName.c_str(), node_flags))
						{
						}
					}

					if (ImGui::IsItemClicked())
						selectedEntityObjectGUI = tempNode;

					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
					{
						// Set payload to carry the index of our item (could be anything)
						ImGui::SetDragDropPayload("DND_DEMO_CELL", &i, sizeof(int));

						// Display preview (could be anything, e.g. when dragging an image we could decide to display
						// the filename and a small preview of the image, etc.)
						ImGui::Text("Move %s", currentEntityName.c_str());
						ImGui::EndDragDropSource();
					}

					if (ImGui::BeginDragDropTarget())
					{
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
						{
							IM_ASSERT(payload->DataSize == sizeof(int));
							int payload_n = *(const int*)payload->Data;

							if ((i - payload_n) > 0)
								entityObjectGUI.moveNode(payload_n, i, false);
							else
								entityObjectGUI.moveNode(payload_n, i, true);

						}
						ImGui::EndDragDropTarget();
					}

				}

				ImGui::PopID();

			}

		}
		ImGui::EndChild();
		ImGui::PopStyleVar();

		
		//for (int i = 0; i < name.size(); i++)
		//{
		//	if (filter.PassFilter(enity[i].name.c_str()))
		//	{
		//		const std::string item = enity[i].name;
		//		//ImGui::Selectable(name[i].c_str());
		//		if (ImGui::TreeNode(enity[i].name.c_str()))
		//		{
		//
		//			if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
		//			{
		//				n_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
		//				if (n_next >= 0 && n_next < name.size())
		//				{
		//					enity[i].name = enity[n_next].name;
		//					enity[n_next].name = item;
		//					ImGui::ResetMouseDragDelta();
		//				}
		//			}
		//			ImGui::TreePop();
		//		}
		//	}
		//}
		//ImGui::Text("next = %i", n_next, ImGui::GetMouseDragDelta(0).y);
		//
		//if (ImGui::TreeNode("Drag to reorder items (simple)"))
		//{
		//	// Simple reordering
		//	static const char* item_names[] = { "Item One", "Item Two", "Item Three", "Item Four", "Item Five" };
		//	for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
		//	{
		//		const char* item = item_names[n];
		//		ImGui::Selectable(item);
		//
		//		if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
		//		{
		//			int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
		//			if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
		//			{
		//				item_names[n] = item_names[n_next];
		//				item_names[n_next] = item;
		//				ImGui::ResetMouseDragDelta();
		//			}
		//		}
		//	}
		//	ImGui::TreePop();
		//}

	}

public:

	Hierarchy() : Widget("Hierarchy", false)
	{
		EntityObjectGUI* temp = new EntityObjectGUI;
		temp->_entity.name = "Square";
		temp->_mesh = new Mesh(Mesh::DefaultGeometry::SQUARE);
		temp->_texture = resourcesTexture[(int)ResourcesTextureIndex::Box];
		temp->visibility = true;
		entityObjectGUI.push_back(temp);

		selectedEntityObjectGUI = entityObjectGUI.findData(0);

		
		//std::string name = "Book ";
		//
		//for (size_t i = 0; i < 15; i++)
		//{
		//	if (i == 5) name = "Pen ";
		//	else if (i == 10) name = "Ruler ";
		//
		//	Entity* temp = new Entity;
		//	temp->name = name + std::to_string(i);
		//	temp->visibility = true;
		//	temp->child.clear();
		//	temp->parent = nullptr;
		//
		//	entity.push_back(temp);
		//}
		//Entity* temp = new Entity;
		//temp->name = "new";
		//temp->visibility = true;
		//temp->child.clear();
		//temp->parent = *entity.begin();
		//
		//temp->parent->child.push_back(temp);
		

	}

};
*/


// v1.0 WorldEditor
/*
class WorldEditor : public Widget {

public:

	Texture* sceneTexture;

private:

	// Inherited via Widget
	virtual void action() override
	{
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 size = ImVec2(Global::wnd->getWidth() * 0.5f, Global::wnd->getHeight() * 0.5f);
		ImGui::SetWindowSize(ImVec2(size.x + 15, size.y + 35));
		//ImGui::Image((void*)(intptr_t)sceneTexture->getTextureID(), size);
		ImGui::GetWindowDrawList()->AddImage((void*)sceneTexture->getTextureID(), ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x,
			pos.y + size.y));// ,ImVec2(pos.x + h / 2, pos.y + w / 2), ImVec2(0, 1), ImVec2(1, 0));
	}

public:

	WorldEditor() : Widget("Scene", false)
	{
		sceneTexture = new Texture(Global::wnd->getWidth(), Global::wnd->getHeight());
	}

};
*/


// v1.0 AssetTracker
/*
class AssetTracker : public Widget {

public:

private:

	// Inherited via Widget
	virtual void action() override
	{

	}

public:

	AssetTracker() : Widget("AssetTracker", false)
	{
	}

};
*/


// v1.0 Property
/*
class Property : public Widget {

public:
	char buf[32] = "Book";


	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 dimension;
	Mesh::DefaultGeometry geometryType;
	glm::vec4 color;
	Texture* texture;

private:

	Texture* tex[6];

	void reset()
	{
		texture = tex[0];

		rotation = glm::vec3(0.0f);
		translation = glm::vec3(0.0f);
		color = glm::vec4(1.0f);
	}

	void transformComponent()
	{
		ImGui::Columns(1, NULL, false);

		ImGui::BeginChild("Transform Component", ImVec2(-FLT_MIN, 150.0f), true, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Transform Component");
				ImGui::EndMenuBar();
			}

			const float eachNextPosX = ImGui::GetCursorPosX() + ((ImGui::GetColumnWidth() / 80.0f) * 17.6f - ImGui::CalcTextSize("X").x) - ImGui::GetScrollX() * ImGui::GetStyle().ItemSpacing.x;
			const float eachHalfPosX = ImGui::GetCursorPosX() + ((ImGui::GetColumnWidth() / 80.0f) * 17.6f - ImGui::CalcTextSize("X").x) / 2.0f - ImGui::GetScrollX() * ImGui::GetStyle().ItemSpacing.x;

			ImGui::SetCursorPosX(eachHalfPosX);
			ImGui::Text("X");
			ImGui::SameLine();

			ImGui::SetCursorPosX(eachNextPosX + eachHalfPosX);
			ImGui::Text("Y");
			ImGui::SameLine();

			ImGui::SetCursorPosX(eachNextPosX + eachNextPosX + eachHalfPosX);
			ImGui::Text("Z");
			ImGui::SameLine();

			ImGui::Separator();


			if (ImGui::DragFloat3("Position", glm::value_ptr(translation), 0.1f, -FLT_MIN, -FLT_MIN, "%.3f")) {

				selectedEntityObjectGUI->_entity.transform->setPosition(translation);
			}
			if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f, -FLT_MIN, -FLT_MIN, "%.3f")) {

				selectedEntityObjectGUI->_entity.transform->setRotation(rotation);
			}
			if (ImGui::DragFloat3("Dimension", glm::value_ptr(dimension), 0.1f, -FLT_MIN, -FLT_MIN, "%.3f")) {

				selectedEntityObjectGUI->_entity.transform->setDimension(dimension);
			}

			
			//ImGui::Text("Position");
			//ImGui::NextColumn();
			//
			//ImGui::PushID("Position X"); ImGui::DragFloat("", &translation.x, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::PushID("Position Y"); ImGui::DragFloat("", &translation.y, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::PushID("Position Z"); ImGui::DragFloat("", &translation.z, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::Separator();
			//
			//ImGui::Text("Rotation");
			//ImGui::NextColumn();
			//
			//ImGui::PushID("Rotation X"); ImGui::DragFloat("", &rotation.x, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::PushID("Rotation Y"); ImGui::DragFloat("", &rotation.y, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::PushID("Rotation Z"); ImGui::DragFloat("", &rotation.z, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::Separator();
			//
			//ImGui::Text("Dimension");
			//ImGui::NextColumn();
			//
			//ImGui::PushID("Dimension X"); ImGui::DragFloat("", &dimension.x, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::PushID("Dimension Y"); ImGui::DragFloat("", &dimension.y, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			//
			//ImGui::PushID("Dimension Z"); ImGui::DragFloat("", &dimension.z, 0.1f, -FLT_MIN, -FLT_MIN, "%.3f");
			//ImGui::NextColumn(); ImGui::PopID();
			

		}
		ImGui::EndChild();

	}

	void meshComponent()
	{
		ImGui::Columns(1, NULL, false);

		ImGui::BeginChild("Material Component", ImVec2(-FLT_MIN, 80.0f), true, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Material Component");
				ImGui::EndMenuBar();
			}

			const char* geometryTypesName[] = { "TRIANGLE", "SQUARE", "CIRCLE", "STADIUM", "PYRAMID", "CUBE", "SPHERE", "CONE", "CYLINDER" };

			if (ImGui::BeginCombo("Mesh", geometryTypesName[static_cast<int>(geometryType)]))
			{
				for (int n = 0; n < IM_ARRAYSIZE(geometryTypesName); n++)
				{
					const bool is_selected = (geometryType == static_cast<Mesh::DefaultGeometry>(n));

					if (ImGui::Selectable(geometryTypesName[n], is_selected))
					{
						if (geometryType != static_cast<Mesh::DefaultGeometry>(n))
						{
							// Switch mesh
							delete selectedEntityObjectGUI->_mesh;
							selectedEntityObjectGUI->_mesh = new Mesh(static_cast<Mesh::DefaultGeometry>(n));

						}

						geometryType = static_cast<Mesh::DefaultGeometry>(n);

					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}

				ImGui::EndCombo();
			}

		}

		ImGui::EndChild();

	}

	// Inherited via Widget
	virtual void action() override
	{

		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(255, 155, 255, 50)); //For visibility
		ImGui::BeginChild("Entity Identity", ImVec2(0, 100.0f), true, ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		{
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("Entity Identity");
				ImGui::EndMenuBar();
			}


			ImGui::Text("Name   : ");
			ImGui::SameLine();

			//static char buf[32] = u8"NIHONGO"; // <- this is how you would write it with C++11, using real kanjis
			ImGui::InputText("", buf, IM_ARRAYSIZE(buf));

		}
		ImGui::EndChild();
		ImGui::PopStyleColor();


		ImGui::Spacing(); ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();


		ImGui::BeginChild("Editor", ImVec2(-FLT_MIN, -FLT_MIN), true);
		{
			transformComponent();
			meshComponent();
		}
		ImGui::EndChild();

	}

public:

	Property() : Widget("Property", false)
	{
		rotation = glm::vec3(0.0f);
		translation = glm::vec3(0.0f);
		dimension = glm::vec3(1.0f);
		color = glm::vec4(1.0f);
		geometryType = Mesh::DefaultGeometry::SQUARE;
	}

};
*/

