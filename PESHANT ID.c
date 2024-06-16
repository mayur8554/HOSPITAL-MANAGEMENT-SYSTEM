 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct Patient 
{
    int PatientID;
    char PatientName[100]; 
    int Age;
    char Disease[100];
    int DaysAdmitted;
};

void AddPatient(struct Patient** patients, int* numPatients, int size);
void RemovePatient(struct Patient** patients, int* numPatients);
void SearchPatient(struct Patient** patients, int numPatients);
void UpdatePatientData(struct Patient** patients, int numPatients);
void DisplayTop3Patients(struct Patient** patients, int numPatients);
void DisplayAllPatients(struct Patient** patients, int numPatients);
void AlreadyStore(struct Patient** patients, int* numPatients);
void Messenger(struct Patient** patients, int numPatients);

int main()
{
    system("color 9F");
    int size = 100;
    struct Patient* patients = (struct Patient*)malloc(size * sizeof(struct Patient));
    int numPatients = 0;
    int choice;

    AlreadyStore(&patients, &numPatients);

    do {
        printf("\n\t\t\t**>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        printf("\t\t\t* Hospital Management System Menu *\n");
        printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>**\n\n");
        printf("\t\t\t1. Add Patient\n");
        printf("\t\t\t2. Display All Patients\n");
        printf("\t\t\t3. Remove Patient\n");
        printf("\t\t\t4. Search Patient\n");
        printf("\t\t\t5. Update Patient Data\n");
        printf("\t\t\t6. Display Top 3 Patients\n");
        printf("\t\t\t7. Messenger for Patients\n");
        printf("\t\t\t8. Exit\n\n");
        printf("\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddPatient(&patients, &numPatients, size);
                break;
            case 2:
                DisplayAllPatients(&patients, numPatients);
                break;
            case 3:
                RemovePatient(&patients, &numPatients);
                break;
            case 4:
                SearchPatient(&patients, numPatients);
                break;
            case 5:
                UpdatePatientData(&patients, numPatients);
                break;
            case 6:
                DisplayTop3Patients(&patients, numPatients);
                break;
            case 7:
                Messenger(&patients, numPatients);
                break;
            case 8:
                printf("\t\t\tTHANKS FOR VISITING.\n");
                break;
            default:
                printf("\t\t\tInvalid choice. Please try again.\n");
        }
    } while (choice != 8);

    free(patients);
    return 0;
}

void AlreadyStore(struct Patient** patients, int* numPatients) {
    (*patients)[0].PatientID = 1;
    strcpy((*patients)[0].PatientName, " RAJEND GOUND");
    (*patients)[0].Age = 45;
    strcpy((*patients)[0].Disease, "Flu");
    (*patients)[0].DaysAdmitted = 5;

    (*patients)[1].PatientID = 2;
    strcpy((*patients)[1].PatientName, " ASMITA THAKUR");
    (*patients)[1].Age = 30;
    strcpy((*patients)[1].Disease, "Malaria");
    (*patients)[1].DaysAdmitted = 7;

    (*patients)[2].PatientID = 3;
    strcpy((*patients)[2].PatientName, "RAVI ARAME");
    (*patients)[2].Age = 50;
    strcpy((*patients)[2].Disease, "COVID-19");
    (*patients)[2].DaysAdmitted = 10;

    *numPatients = 3;
}

void DisplayAllPatients(struct Patient** patients, int numPatients) {
    if (numPatients == 0) {
        printf("\t\t\tPatient database is empty. No patients to display.\n");
        return;
    }

    printf("\n");
    printf("\t\t\t+-----------+----------------+-----+----------+---------------+\n");
    printf("\t\t\t| PatientID |  Patient Name  | Age | Disease  | Days Admitted |\n");
    printf("\t\t\t+-----------+----------------+-----+----------+---------------+\n");
    
    for (int i = 0; i < numPatients; i++) {
        printf("\t\t\t| %-9d | %-14s | %-3d | %-8s | %-13d |\n",
               (*patients)[i].PatientID, (*patients)[i].PatientName, (*patients)[i].Age, (*patients)[i].Disease, (*patients)[i].DaysAdmitted);
    }
    
    printf("\t\t\t+-----------+----------------+-----+----------+---------------+\n");
}

void AddPatient(struct Patient** patients, int* numPatients, int size) {
    if (*numPatients >= size) {
        printf("\t\t\tPatient database is full. Cannot add more patients.\n");
        return; 
    }

    struct Patient newPatient;
    printf("\t\t\tEnter Patient ID: ");
    scanf("%d", &newPatient.PatientID);
    printf("\t\t\tEnter Patient Name: ");
    scanf("%s", newPatient.PatientName);
    printf("\t\t\tEnter Age: ");
    scanf("%d", &newPatient.Age);
    printf("\t\t\tEnter Disease: ");
    scanf("%s", newPatient.Disease);
    printf("\t\t\tEnter Days Admitted: ");
    scanf("%d", &newPatient.DaysAdmitted); 

    (*patients)[*numPatients] = newPatient;
    (*numPatients)++;
    printf("\t\t\tPatient added successfully.\n");
}

void RemovePatient(struct Patient** patients, int* numPatients) {
    if (*numPatients == 0) {
        printf("\t\t\tPatient database is empty. Cannot remove a patient.\n");
        return;
    }

    int choice;
    printf("\t\t\tHow would you like to remove the patient?\n");
    printf("\t\t\t1. Remove by Patient ID\n");
    printf("\t\t\t2. Remove by Patient Name\n");
    printf("\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int IDToRemove;
        printf("\t\t\tEnter the Patient ID of the patient you want to remove: ");
        scanf("%d", &IDToRemove);

        int i, j;
        int found = 0;
        for (i = 0; i < *numPatients; i++) {
            if ((*patients)[i].PatientID == IDToRemove) {
                for (j = i; j < *numPatients - 1; j++) {
                    (*patients)[j] = (*patients)[j+1];
                }
                (*numPatients)--;
                printf("\t\t\tPatient with ID %d is removed.\n", IDToRemove);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with ID %d not found.\n", IDToRemove);
        }
    } else if (choice == 2) {
        char NameToRemove[100];
        printf("\t\t\tEnter the name of the patient you want to remove: ");
        scanf("%s", NameToRemove);
        int i, j;
        int found = 0;
        for (i = 0; i < *numPatients; i++) {
            if (strcmp((*patients)[i].PatientName, NameToRemove) == 0) {
                for (j = i; j < *numPatients - 1; j++) {
                    (*patients)[j] = (*patients)[j+1];
                }
                (*numPatients)--;
                printf("\t\t\tPatient with Name '%s' is removed.\n", NameToRemove);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with Name '%s' not found.\n", NameToRemove);
        }
    } else {
        printf("\t\t\tInvalid choice.\n");
    }
}

void SearchPatient(struct Patient** patients, int numPatients) {
    if (numPatients == 0) {
        printf("\t\t\tPatient database is empty. Cannot search for a patient.\n");
        return;
    }

    int choice;
    printf("\t\t\tHow would you like to search the patient?\n");
    printf("\t\t\t1. Search by Patient ID\n");
    printf("\t\t\t2. Search by Patient Name\n");
    printf("\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int SearchID;
        printf("\t\t\tEnter the Patient ID of the patient you want to search: ");
        scanf("%d", &SearchID);

        int i, found = 0;
        for (i = 0; i < numPatients; i++) {
            if ((*patients)[i].PatientID == SearchID) {
                printf("\t\t\tPatient found:\n");
                printf("\t\t\tPatient ID: %d  Patient Name: %s  Age: %d  Disease: %s  Days Admitted: %d\n",
                       (*patients)[i].PatientID, (*patients)[i].PatientName, (*patients)[i].Age, (*patients)[i].Disease, (*patients)[i].DaysAdmitted);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with ID %d not found.\n", SearchID);
        }
    } else if (choice == 2) {
        char SearchName[100];
        printf("\t\t\tEnter the name of the patient you want to search: ");
        scanf("%s", SearchName);

        int i, found = 0;
        for (i = 0; i < numPatients; i++) {
            if (strcmp((*patients)[i].PatientName, SearchName) == 0) {
                printf("\t\t\tPatient found:\n");
                printf("\t\t\tPatient ID: %d  Patient Name: %s  Age: %d  Disease: %s  Days Admitted: %d\n",
                       (*patients)[i].PatientID, (*patients)[i].PatientName, (*patients)[i].Age, (*patients)[i].Disease, (*patients)[i].DaysAdmitted);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with Name '%s' not found.\n", SearchName);
        }
    } else {
        printf("\t\t\tInvalid choice.\n");
    }
}

void UpdatePatientData(struct Patient** patients, int numPatients) {
    if (numPatients == 0) {
        printf("\t\t\tPatient database is empty. Cannot update data.\n");
        return;
    }

    int choice;
    printf("\t\t\tHow would you like to update the patient data?\n");
    printf("\t\t\t1. Update by Patient ID\n");
    printf("\t\t\t2. Update by Patient Name\n");
    printf("\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int UpdateID;
        printf("\t\t\tEnter the Patient ID of the patient you want to update: ");
        scanf("%d", &UpdateID);

        int i, found = 0;
        for (i = 0; i < numPatients; i++) {
            if ((*patients)[i].PatientID == UpdateID) {
                printf("\t\t\tEnter new data for the patient:\n");
                printf("\t\t\tEnter Patient Name: ");
                scanf("%s", (*patients)[i].PatientName);
                printf("\t\t\tEnter Age: ");
                scanf("%d", &(*patients)[i].Age);
                printf("\t\t\tEnter Disease: ");
                scanf("%s", (*patients)[i].Disease);
                printf("\t\t\tEnter Days Admitted: ");
                scanf("%d", &(*patients)[i].DaysAdmitted);
                printf("\t\t\tPatient data updated successfully.\n");
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with ID %d not found.\n", UpdateID);
        }
    } else if (choice == 2) {
        char UpdateName[100];
        printf("\t\t\tEnter the name of the patient you want to update: ");
        scanf("%s", UpdateName);

        int i, found = 0;
        for (i = 0; i < numPatients; i++) {
            if (strcmp((*patients)[i].PatientName, UpdateName) == 0) {
                printf("\t\t\tEnter new data for the patient:\n");
                printf("\t\t\tEnter Patient ID: ");
                scanf("%d", &(*patients)[i].PatientID);
                printf("\t\t\tEnter Age: ");
                scanf("%d", &(*patients)[i].Age);
                printf("\t\t\tEnter Disease: ");
                scanf("%s", (*patients)[i].Disease);
                printf("\t\t\tEnter Days Admitted: ");
                scanf("%d", &(*patients)[i].DaysAdmitted);
                printf("\t\t\tPatient data updated successfully.\n");
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with Name '%s' not found.\n", UpdateName);
        }
    } else {
        printf("\t\t\tInvalid choice.\n");
    }
}

void DisplayTop3Patients(struct Patient** patients, int numPatients) {
    if (numPatients < 3) {
        printf("\t\t\tNot enough patients to display top 3.\n");
        return;
    }

    struct Patient topPatients[3];
    int i, j;

    for (i = 0; i < 3; i++) {
        topPatients[i] = (*patients)[i];
    }

    for (i = 3; i < numPatients; i++) {
        for (j = 0; j < 3; j++) {
            if ((*patients)[i].DaysAdmitted > topPatients[j].DaysAdmitted) {
                topPatients[j] = (*patients)[i];
                break;
            }
        }
    }

    printf("\n");
    printf("\t\t\t+-----------+----------------+-----+----------+---------------+\n");
    printf("\t\t\t| PatientID |  Patient Name  | Age | Disease  | Days Admitted |\n");
    printf("\t\t\t+-----------+----------------+-----+----------+---------------+\n");
    
    for (i = 0; i < 3; i++) {
        printf("\t\t\t| %-9d | %-14s | %-3d | %-8s | %-13d |\n",
               topPatients[i].PatientID, topPatients[i].PatientName, topPatients[i].Age, topPatients[i].Disease, topPatients[i].DaysAdmitted);
    }
    
    printf("\t\t\t+-----------+----------------+-----+----------+---------------+\n");
}

void Messenger(struct Patient** patients, int numPatients) {
    if (numPatients == 0) {
        printf("\t\t\tPatient database is empty. Cannot send messages.\n");
        return;
    }

    int choice;
    printf("\t\t\tHow would you like to send the message?\n");
    printf("\t\t\t1. Send by Patient ID\n");
    printf("\t\t\t2. Send by Patient Name\n");
    printf("\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int MessageID;
        printf("\t\t\tEnter the Patient ID of the patient you want to message: ");
        scanf("%d", &MessageID);

        int i, found = 0;
        for (i = 0; i < numPatients; i++) {
            if ((*patients)[i].PatientID == MessageID) {
                printf("\t\t\tEnter your message: ");
                char message[256];
                getchar();  // to clear the newline character left in the buffer
                fgets(message, 256, stdin);
                printf("\t\t\tMessage sent to %s (Patient ID: %d).\n", (*patients)[i].PatientName, (*patients)[i].PatientID);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with ID %d not found.\n", MessageID);
        }
    } else if (choice == 2) {
        char MessageName[100];
        printf("\t\t\tEnter the name of the patient you want to message: ");
        scanf("%s", MessageName);

        int i, found = 0;
        for (i = 0; i < numPatients; i++) {
            if (strcmp((*patients)[i].PatientName, MessageName) == 0) {
                printf("\t\t\tEnter your message: ");
                char message[256];
                getchar();  // to clear the newline character left in the buffer
                fgets(message, 256, stdin);
                printf("\t\t\tMessage sent to %s (Patient ID: %d).\n", (*patients)[i].PatientName, (*patients)[i].PatientID);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t\t\tPatient with Name '%s' not found.\n", MessageName);
        }
    } else {
        printf("\t\t\tInvalid choice.\n");
    }
}
