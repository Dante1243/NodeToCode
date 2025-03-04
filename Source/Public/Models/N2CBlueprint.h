// Copyright (c) 2025 Nick McClure (Protospatial). All Rights Reserved.

/**
 * @file N2CBlueprint.h
 * @brief Blueprint-related data type definitions for the Node to Code plugin
 */

#pragma once

#include "CoreMinimal.h"
#include "N2CNode.h"
#include "Utils/N2CLogger.h"
#include "N2CBlueprint.generated.h"

/**
 * @struct FN2CVersion
 * @brief Version information for N2CStruct format
 */
USTRUCT(BlueprintType)
struct FN2CVersion
{
    GENERATED_BODY()

    /** Version string, always "1.0.0" in current spec */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    FString Value;

    FN2CVersion() : Value(TEXT("1.0.0")) {}
};

/**
 * @enum EN2CBlueprintType
 * @brief Defines the type of Blueprint being processed
 */
UENUM(BlueprintType)
enum class EN2CBlueprintType : uint8
{
    /** Normal blueprint. */
    Normal  UMETA(DisplayName = "Blueprint Class"),
    /** Blueprint that is const during execution (no state graph and methods cannot modify member variables). */
    Const   UMETA(DisplayName = "Const Blueprint Class"),
    /** Blueprint that serves as a container for macros to be used in other blueprints. */
    MacroLibrary UMETA(DisplayName = "Blueprint Macro Library"),
    /** Blueprint that serves as an interface to be implemented by other blueprints. */
    Interface UMETA(DisplayName = "Blueprint Interface"),
    /** Blueprint that handles level scripting. */
    LevelScript UMETA(DisplayName = "Level Blueprint"),
    /** Blueprint that serves as a container for functions to be used in other blueprints. */
    FunctionLibrary UMETA(DisplayName = "Blueprint Function Library"),
};

/**
 * @struct FN2CMetadata
 * @brief Required metadata about the Blueprint
 */
USTRUCT(BlueprintType)
struct FN2CMetadata
{
    GENERATED_BODY()

    /** Name of the Blueprint */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    FString Name;

    /** Type of the Blueprint */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    EN2CBlueprintType BlueprintType;

    /** The Blueprint class this graph belongs to */                                                                                                                                                                                 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")                                                                                                                                                             
    FString BlueprintClass; 

    FN2CMetadata() : Name(TEXT("")), BlueprintType(EN2CBlueprintType::Normal), BlueprintClass(TEXT("")) {}
};

/**
 * @struct FN2CFlows 
 * @brief Contains all execution and data flow connections between nodes
 */
USTRUCT(BlueprintType)
struct FN2CFlows
{
    GENERATED_BODY()

    /** Execution array. Each entry is a chain like "N1->N2->N3" */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    TArray<FString> Execution;

    /** Data connections: a mapping from "N1.P4" to "N2.P3" */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    TMap<FString, FString> Data;

    FN2CFlows()
    {
    }
};

/**
 * @enum EN2CGraphType
 * @brief Defines the type of Blueprint graph
 */
UENUM(BlueprintType)
enum class EN2CGraphType : uint8
{
    /** The main event graph */
    EventGraph       UMETA(DisplayName = "Event Graph"),
    /** A user-created function */
    Function        UMETA(DisplayName = "Function"),
    /** A collapsed graph/composite node */
    Composite       UMETA(DisplayName = "Composite"),
    /** A macro graph */
    Macro          UMETA(DisplayName = "Macro"),
    /** A construction script */
    Construction    UMETA(DisplayName = "Construction Script"),
    /** An animation graph */
    Animation      UMETA(DisplayName = "Animation")
};

/**
 * @struct FN2CGraph
 * @brief Represents a single graph within the Blueprint
 */
USTRUCT(BlueprintType)
struct FN2CGraph
{
    GENERATED_BODY()

    /** Name of the graph */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    FString Name;

    /** Type of graph */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    EN2CGraphType GraphType;

    /** Array of all nodes in this graph */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    TArray<FN2CNodeDefinition> Nodes;

    /** Execution and data flow connections for this graph */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    FN2CFlows Flows;

    FN2CGraph()
        : GraphType(EN2CGraphType::EventGraph)
    {
    }

    /** Validates the graph structure */
    bool IsValid() const;
};

/**
 * @struct FN2CBlueprint
 * @brief Top-level container for Blueprint graph data
 */
USTRUCT(BlueprintType)
struct FN2CBlueprint
{
    GENERATED_BODY()

    /** Version information (always "1.0.0" in current spec) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    FN2CVersion Version;

    /** Required metadata about the Blueprint */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    FN2CMetadata Metadata;

    /** Array of all graphs in the Blueprint */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node to Code")
    TArray<FN2CGraph> Graphs;

    FN2CBlueprint()
    {
        // Version is automatically initialized to "1.0.0" by FN2CVersion constructor
    }

    /** Validates the Blueprint structure and its enums */
    bool IsValid() const;
};
